//
//  CGPlayerVideoOutput.h
//  CGPlayer
//
//  Created by Jason on 2021/5/10.
//

#import <Foundation/Foundation.h>
@import CoreVideo;

NS_ASSUME_NONNULL_BEGIN

@class AVPlayerVideoOutput;
@protocol CGPlayerVideoOutputDelegate <NSObject>
@optional

/**
 回调将要渲染的帧数据
 
 @param output 调用该方法的 AVTPlayerVideoOutput 对象
 @param frame 将要渲染帧数据。格式包括kPixelFormatType_32BGRA, kPixelFormatType_420YpCbCr8
 @param pts 显示时间戳 单位ms
 @discussion frame内存周期由AVTPlayer维护
 @warning 如果不需要获取帧数据最好不要设置, 如果设置, 则多进行一个data转CVPixelBufferRef

 @since v1.0.0
 */
- (void)output:(nonnull AVPlayerVideoOutput *)output willRenderFrame:(nullable CVPixelBufferRef)frame pts:(int64_t)pts;

/**
 回调将要渲染的帧数据
 
 @param output 调用该方法的 AVTPlayerVideoOutput 对象
 @param buffer 将要渲染帧数据。格式包括kPixelFormatType_32BGRA, kPixelFormatType_420YpCbCr8
 @param pts 显示时间戳 单位ms
 @discussion buffer的内存周期由AVTPlayer维护
 @since v1.0.0
 */
- (void)output:(nonnull AVPlayerVideoOutput *)output willRenderBuffer:(nullable UInt8 *)buffer pts:(int64_t)pts width:(NSInteger)width height:(NSInteger)height;

- (void)output:(nonnull AVPlayerVideoOutput *)output error:(NSError *)error;

@end

#pragma mark BufferAttributeKeys
typedef NSString *RawOutputOptionsKey NS_STRING_ENUM;
extern RawOutputOptionsKey const kPixelBufferPixelFormatTypeKey; // NSNumber
extern RawOutputOptionsKey const kPixelBufferWidthKey;           // NSNumber
extern RawOutputOptionsKey const kPixelBufferHeightKey;          // NSNumber

enum {
    kPixelFormatType_32BGRA         = 'BGRA',     /* 32 bit BGRA */
    kPixelFormatType_420YpCbCr8     = 'y420',     /* Planar Component Y'CbCr 8-bit 4:2:0 */
};
@interface AVPlayerVideoOutput : NSObject

- (instancetype)initWithOutputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings;

@property (nonatomic, weak) id<CGPlayerVideoOutputDelegate>outputDelegate;

@end

NS_ASSUME_NONNULL_END

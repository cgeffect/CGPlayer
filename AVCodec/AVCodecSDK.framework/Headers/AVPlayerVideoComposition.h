//
//  CGPlayerVideoComposition.h
//  CGPlayer
//
//  Created by Jason on 2021/5/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@import CoreVideo;

@class AVPlayerVideoComposition;
@protocol CGVideoCompositing <NSObject>

/**
 回调将要渲染的帧数据
 
 @param asyncVideoCompositionRequest 调用该方法的 AVTPlayerVideoComposition 对象
 @param frame 将要渲染帧数据。格式包括kPixelFormatType_32BGRA, kPixelFormatType_420YpCbCr8
 @param pts 显示时间戳 单位ms
 @discussion frame内存周期由AVTPlayerVideoComposition维护, 代理执行完毕即被回收
 @warning 如果不需要获取帧数据最好不要设置, 如果设置, 则多进行一个data转CVPixelBufferRef

 @since v1.0.0
 */
- (void)startVideoCompositionRequest:(AVPlayerVideoComposition *)asyncVideoCompositionRequest willRenderFrame:(nullable CVPixelBufferRef)frame pts:(int64_t)pts;

/**
 回调将要渲染的帧数据
 
 @param asyncVideoCompositionRequest 调用该方法的 AVTPlayerVideoComposition 对象
 @param buffer 将要渲染帧数据。格式包括kPixelFormatType_32BGRA, kPixelFormatType_420YpCbCr8
 @param pts 显示时间戳 单位ms
 @discussion buffer的内存周期由AVTPlayerVideoComposition维护, 代理执行完毕即被回收
 
 @since v1.0.0
 */
- (void)startVideoCompositionRequest:(AVPlayerVideoComposition *)asyncVideoCompositionRequest willRenderBuffer:(nullable UInt8 *)buffer pts:(int64_t)pts width:(NSInteger)width height:(NSInteger)height;

@end

@interface AVPlayerVideoComposition : NSObject

- (instancetype)initWithVideoCompositionSettings:(nullable NSDictionary<NSString *, id> *)videoCompositionSettings;

@property(nonatomic, weak)id<CGVideoCompositing>videoCompositing;

/**
 是否启用CGVideoCompositing回调, YES: 启用, NO: 禁用
 @discussion 支持动态配置CGVideoCompositing代理输出, 在AVTPlayer播放视频的过程中, 无需修改代理, 实现动态的代理配置
 
 @since v1.0.0
 */
@property(nonatomic, assign)BOOL enableVideoCompositing;

/*!
    @method            sourceFrame
    @abstract       Returns the source CVPixelBufferRef
*/
- (nullable CVPixelBufferRef)sourceFrame;
/*!
    @method            sourceBuffer
    @abstract       Returns the source CVPixelBufferRef
*/
- (nullable UInt8 *)sourceBuffer;

/* callback the custom compositor should call when composition succeeded */
- (void)finishWithComposedVideoFrame:(nonnull CVPixelBufferRef)composedVideoFrame;

- (void)finishWithComposedVideoBuffer:(nonnull UInt8 *)composedVideoBuffer;

/* callback the custom compositor should call when composition failed. The error parameter should describe the actual error. */
- (void)finishWithError:(NSError *)error;

/* callback the custom compositor should call for a request that has been cancelled. */
- (void)finishCancelledRequest;
@end

NS_ASSUME_NONNULL_END

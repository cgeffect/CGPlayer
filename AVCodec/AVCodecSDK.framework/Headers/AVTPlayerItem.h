//
//  CGPlayerItem.h
//  CGPlayer
//
//  Created by Jason on 2021/4/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@import CoreMedia;

@interface AVTPlayerItem : NSObject

- (instancetype)initWithURL:(NSURL *)URL;

/**
 视频URL
 
 @since v1.0.0
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 AVTPlayerItem 的总播放时间ms
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) int64_t duration;

/**
 视频流的宽高
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) CGSize presentationSize;

/**
 视频实际渲染的宽高, 如果有旋转角度, 则为转为竖屏的宽高
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) CGSize renderSize;

/**
 视频流的帧率, fps
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) int frameRate;

/**
 帧间隔
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) int perFrameDuration;

/**
 视频流的码率，单位 kb/s
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) double kbps;

/**
 转场的时间部分, 单位 毫秒
 
 @since v1.0.0
 */
@property (nonatomic, assign) int transitionDuration;

/**
 出场顺序,  从0开始依次递增
 
 @since v1.0.0
 */
@property (nonatomic, assign) int playIndex;

@end

NS_ASSUME_NONNULL_END

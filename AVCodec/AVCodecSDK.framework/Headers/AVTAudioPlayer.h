//
//  AVTAudioPlayer.h
//  AVTPlayer
//
//  Created by Jason on 2021/4/30.
//

#import <Foundation/Foundation.h>
#import <AVCodecSDK/AVTAudioFormat.h>

NS_ASSUME_NONNULL_BEGIN

/**
 AVTAudioPlayer 的播放状态
 
 @since v1.0.0
 */
typedef NS_ENUM(NSInteger, AVTAudioPlayerStatus) {
    
    /**
     AVTAudioPlayer 未知状态，只会作为 init 后的初始状态，开始播放之后任何情况下都不会再回到此状态。
     @since v1.0.0
     */
    AVTAudioPlayerStatusUnknow = 0,
    
    /**
     AVTAudioPlayer 播放组件准备完成，准备开始播放。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusReady,
    
    /**
     AVTAudioPlayer 正在播放状态。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusPlaying,
    
    /**
     AVTAudioPlayer 暂停状态。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusPaused,
    
    /**
     AVTAudioPlayer 继续播放状态。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusResumed,
    
    /**
     @abstract AVTAudioPlayer 停止状态
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusStopped,
    
    /**
     AVTAudioPlayer 播放完成
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusCompleted,
    
    /**
     AVTAudioPlayer 错误状态，播放出现错误时会出现此状态。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusError,
    
    /**
     AVTAudioPlayer 销毁。
     
     @since v1.0.0
     */
    AVTAudioPlayerStatusDestroyed,
};

@class AVTAudioPlayer;
@protocol AVTAudioPlayerDelegate <NSObject>
@optional

/**
 告知代理对象 AVTAudioPlayer 即将开始进入后台播放任务
 
 @param player 调用该代理方法的 AVTAudioPlayer 对象
 
 @since v1.0.0
 */
- (void)playerWillBeginBackgroundTask:(nonnull AVTAudioPlayer *)player;

/**
 告知代理对象 AVTAudioPlayer 即将结束后台播放状态任务
 
 @param player 调用该方法的 AVTAudioPlayer 对象
 
 @since v1.0.0
 */
- (void)playerWillEndBackgroundTask:(nonnull AVTAudioPlayer *)player;

/**
 告知代理对象播放器状态变更
 
 @param player 调用该方法的 AVTAudioPlayer 对象
 @param status  变更之后的 AVTAudioPlayer 状态
 
 @since v1.0.0
 */
- (void)player:(nonnull AVTAudioPlayer *)player statusChanged:(AVTAudioPlayerStatus)status;

/**
 告知代理对象播放器因错误停止播放
 
 @param player 调用该方法的 AVTAudioPlayer 对象
 @param error  携带播放器停止播放错误信息的 NSError 对象
 
 @since v1.0.0
 */
- (void)player:(nonnull AVTAudioPlayer *)player stoppedWithError:(nullable NSError *)error;

/**
 已播放进度
 
 @param player 调用该方法的 AVTAudioPlayer 对象
 @param progress  当前播放的进度, 单位ms。
 
 @since v1.0.0
 */
- (void)player:(nonnull AVTAudioPlayer *)player progress:(int64_t)progress;

/**
 seekTo 完成的回调通知
 
 @param player 调用该方法的 AVTAudioPlayer 对象
 
 @since v1.0.0
 */
- (void)player:(nonnull AVTAudioPlayer *)player seekToCompleted:(BOOL)isCompleted;

@end

@interface AVTAudioPlayer : NSObject
/**
 单例播放器对象
 
 @since v1.0.0
 */
+(AVTAudioPlayer *)sharePlayer;

/**
 资源文件, 支持mp3, mp4, mov
 
 @since v1.0.0
 */
- (void)loadWithURL:(NSString *)url;

/**
 pcm数据, 调试使用, 在(loadWithURL:)执行之前赋值
 
 @since v1.0.0
 */
@property(nonatomic, strong) NSString *pcmPath;

/**
 音频播放代理
 
 @since v1.0.0
 */
@property(weak, nullable) id<AVTAudioPlayerDelegate> delegate;

/**
 音频轨道时长
 
 @since v1.0.0
 */
@property(readonly) NSTimeInterval durationMs;

/**
 资源URL
 
 @since v1.0.0
 */
@property(readonly, nullable) NSURL *url;

/**
 CGAVPlayer 的播放状态
 
 @since v1.0.0
 */
@property (nonatomic, readonly) AVTAudioPlayerStatus status;

/**
 播放的声音 0 - 1, 0 静音, 1 最大声音
 
 @since v1.0.0
 */
@property float volume;

/**
 循环播放的次数, -1 无线循环
 
 @since v1.0.0
 */
@property NSInteger numberOfLoops;

/* settings */
@property(readonly) NSDictionary<NSString *, id> *settings; /* returns a settings dictionary with keys as described in AVAudioSettings.h */

/* returns the format of the audio data */
//@property(readonly) AVTAudioFormat *format;
@property(nonatomic, strong, readonly)AVTAudioFormat *audioFormat;


#pragma mark control
/**
 开始播放
 
 @since v1.0.0
 */
- (void)play;

/**
 当播放器处于暂停状态时调用该方法可以使播放器继续播放
 
 @since v1.0.0
 */
- (void)resume;

/**
 当播放器处于 playing状态时调用该方法可以暂停播放器
 
 @since v1.0.0
 */
- (void)pause;

/**
 停止播放器
 
 @since v1.0.0
 */
- (void)stop;

/**
 快速定位到指定播放时间点
 
 @since v1.0.0
 */
- (void)seekTo:(float)time;

/**
 标记seek事件
 @param isSeek
 <pre> @textblock
    holdSeek:YES
    seekToTime:time
    holdSeek:NO
 @/textblock </pre>
 
 @since v1.0.0
 */
- (void)holdSeek:(BOOL)isSeek;

@end


NS_ASSUME_NONNULL_END

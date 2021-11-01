# CGCodecSDK

音视频播放器

1. 视频播放

FFmpeg -> VideoToolbox -> OpenGL
2. 音频播放
FFmpeg -> PCM -> AudioQueue
3. 精准seek, seek帧回调

4. 音频播放器

---
接口文档
/**
 CGAVPlayer 的播放状态
 
 @since v1.0.0
 */
typedef NS_ENUM(NSInteger, CGPlayerStatus) {
    
    /**
     CGAVPlayer 未知状态，只会作为 init 后的初始状态，开始播放之后任何情况下都不会再回到此状态。
     @since v1.0.0
     */
    CGPlayerStatusUnknow = 0,
    
    /**
     CGAVPlayer 播放组件准备完成，准备开始播放。
     
     @since v1.0.0
     */
    CGPlayerStatusReady,
    
    /**
     CGAVPlayer 正在播放状态。
     
     @since v1.0.0
     */
    CGPlayerStatusPlaying,
    
    /**
     CGAVPlayer 暂停状态。
     
     @since v1.0.0
     */
    CGPlayerStatusPaused,
    
    /**
     CGAVPlayer 继续播放状态。
     
     @since v1.0.0
     */
    CGPlayerStatusResumed,
    
    /**
     @abstract CGAVPlayer 停止状态
     
     @since v1.0.0
     */
    CGPlayerStatusStopped,
    
    /**
     CGAVPlayer 播放完成
     
     @since v1.0.0
     */
    CGPlayerStatusCompleted,
    
    /**
     CGAVPlayer 错误状态，播放出现错误时会出现此状态。
     
     @since v1.0.0
     */
    CGPlayerStatusError,
    
    /**
     CGAVPlayer 销毁。
     
     @since v1.0.0
     */
    CGPlayerStatusDestroyed,
};

typedef NS_ENUM(NSInteger, AVTPlayerFirstRenderType) {
    AVTPlayerFirstRenderTypeVideo = 0, // 视频
    AVTPlayerFirstRenderTypeAudio // 音频
};

@class CGAVPlayer;
@protocol CGPlayerDelegate <NSObject>
@optional

/**
 告知代理对象 CGAVPlayer 即将开始进入后台播放任务
 
 @param player 调用该代理方法的 CGAVPlayer 对象
 
 @since v1.0.0
 */
- (void)playerWillBeginBackgroundTask:(nonnull CGAVPlayer *)player;

/**
 告知代理对象 CGAVPlayer 即将结束后台播放状态任务
 
 @param player 调用该方法的 CGAVPlayer 对象
 
 @since v1.0.0
 */
- (void)playerWillEndBackgroundTask:(nonnull CGAVPlayer *)player;

/**
 告知代理对象播放器状态变更
 
 @param player 调用该方法的 CGAVPlayer 对象
 @param status  变更之后的 CGAVPlayer 状态
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player statusChanged:(CGPlayerStatus)status;

/**
 告知代理对象播放器因错误停止播放
 
 @param player 调用该方法的 CGAVPlayer 对象
 @param error  携带播放器停止播放错误信息的 NSError 对象
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player stoppedWithError:(nullable NSError *)error;

/**
 已播放进度
 
 @param player 调用该方法的 CGAVPlayer 对象
 @param progress  当前播放的进度, 单位ms。
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player progress:(int64_t)progress;

/**
 音视频渲染首帧回调通知
 
 @param player 调用该方法的 CGAVPlayer 对象
 @param firstRenderType 音视频首帧回调通知类型
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player firstRender:(AVTPlayerFirstRenderType)firstRenderType;

/**
 视频宽高数据回调通知

 @param player 调用该方法的 CGAVPlayer 对象
 @param width 视频流宽
 @param height 视频流高
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player width:(int)width height:(int)height;

/**
 seekTo 完成的回调通知
 
 @param player 调用该方法的 CGAVPlayer 对象
 
 @since v1.0.0
 */
- (void)player:(nonnull CGAVPlayer *)player seekToCompleted:(BOOL)isCompleted;

@end

/**
 getScreenShotWithCompletionHandler 截图操作为异步，
 完成后将通过 ScreenShotWithCompletionHandler 类型的 block 回调返回 UIImage 类型图片数据。
 
 @since v1.0.0
 */
typedef void (^ScreenShotWithCompletionHandler)(UIImage * _Nullable image);

@interface CGAVPlayer : NSObject

- (instancetype)initWithPlayerItem:(nullable AVTPlayerItem *)item;

- (AVTPlayerLayer *)playerLayerWithFrame:(CGRect)frame;

@property (nonatomic, weak) id<CGPlayerDelegate>delegate;

@property (nonatomic, strong) AVTPlayerItem *playerItem;
/**
 CGAVPlayer 的播放状态
 
 @since v1.0.0
 */
@property (nonatomic, readonly) CGPlayerStatus status;

/**
 回调方法的调用队列
 @discussion 默认是在主线程
 
 @since v1.0.0
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

#pragma mark play info
/**
 指示当前 CGAVPlayer 是否处于正在播放状态
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly, getter=isPlaying) BOOL playing;

/**
 CGAVPlayer 的当前播放时间
 
 @since v1.0.0
 */
@property (nonatomic, assign, readonly) CMTime currentTime;

/**
 是否渲染画面，默认为 YES
 
 @since v1.0.0
 */
@property (nonatomic, assign) BOOL enableRender;

/**
 变速播放，范围是 0.5-2.0，默认是 1.0
 
 @since v1.0.0
 */
@property (nonatomic, assign) double playSpeed;

/**
 视频剪裁播放，配置参数：(x, y, width, height)，尺寸需是 4 的倍数，默认全视频画面
 
 @warning 该属性只播放和渲染指定位置的画面，其中 x、y、width、height 值均取整使用，若播放新链接需裁剪，则每次新链接 play 前重新设置；若需重置为全视频画面，传 CGRectZero 即可
 
 @since v1.0.0
 */
@property (nonatomic, assign) CGRect videoClipFrame;

/**
 是否循环播放，默认为 NO
 
 @since v1.0.0
 */
@property (nonatomic, assign) BOOL loopPlay;

/**
 视频封面
 
 @since v1.0.0
 */
@property (nonatomic, assign) UIImage *videoCover;

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
- (void)seekTo:(CMTime)time;

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

#pragma mark AVPlayerMediaControl

/**
 是否需要静音 CGAVPlayer，默认值为NO
 
 @since v1.0.0
 */
@property (nonatomic, assign, getter=isMute) BOOL mute;

/**
 *  设置音量，范围是0-3.0，默认是1.0
 *
 *  @param volume 音量
 *
 *  @since v1.0.0
 */
- (void)setVolume:(float)volume;

/**
 *  获取音量
 *
 *  @since v1.0.0
 *
 *  @return 音量
 */
- (float)getVolume;

/**
 *  截图
 *  @param handle 类型 ScreenShotWithCompletionHandler block 。
 *
 *  @discussion 截图操作为异步，完成后将通过 handle 回调返回 UIImage 类型图片数据。
 *              该功能只支持软解
 *
 *  @since v1.0.0
 *
 */
- (void)getScreenShotWithCompletionHandler:(nullable ScreenShotWithCompletionHandler)handle;

#pragma mark Output

/**
 *  设置AVTPlayerVideoOutput
 *  @discussion 需要获取渲染视频帧数据则创建
 *
 *  @since v1.0.0
 */
- (void)addVideoOutput:(AVPlayerVideoOutput *)output;

/**
 *  移除AVTPlayerVideoOutput
 *
 *  @since v1.0.0
 */
- (void)removeVideoOutput:(AVPlayerVideoOutput *)output;

/**
 *  设置AVTPlayerAudioOutput
 *
 *  @since v1.0.0
 */
- (void)addAudioOutput:(AVPlayerAudioOutput *)output;

/**
 *  移除AVTPlayerAudioOutput
 *
 *  @since v1.0.0
 */
- (void)removeAudioOutput:(AVPlayerAudioOutput *)output;

/*!
 @property videoComposition
 @abstract Indicates the video composition settings to be applied during playback.
 */
@property (nonatomic, copy, nullable) AVPlayerVideoComposition *videoComposition;

/*!
 @property customVideoCompositor
 @abstract Indicates the custom video compositor instance.
 @discussion
     This property is nil if there is no video compositor, or if the internal video compositor is in use. This reference can be used to provide
    extra context to the custom video compositor instance if required.
 */
@property (nonatomic, readonly, nullable) id<CGVideoCompositing> customVideoCompositor;


@end

NS_ASSUME_NONNULL_END

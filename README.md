# CGCodecSDK

CGCodecSDK 是一个适用于 iOS 的音视频本地播放器 SDK，可高度定制化UI. 

SDK 的 Github 地址：https://github.com/cgeffect/CGPlayer

功能特性

- [x] 高可定制
- [x] 支持播放器音量设置
- [x] 支持纯音频播放
- [x] 支持软硬解自动切换
- [x] 支持 H.265 格式播放
- [x] 支持 H.264 格式播放
- [x] 支持点播倍速播放
- [x] 支持视频根据旋转角度自动旋转
- [x] 支持播放音量放大
- [x] 支持播放预加载
- [x] 支持循环播放
- [x] 支持 seekTo 完成的回调
- [x] 新增倍数播放功能（0.5-2）
- [x] 新增音视频渲染首帧回调
- [x] 支持后台自动暂停, 回到前台自动播放

## 快速开始

#### 手动导入  

- 根据需要，将 AVCodecSDK.framework 文件加入到工程中；
- Build Setting 下 Other Linker Flags 中添加 -ObjC
- Build Phases 下 Link Binary With Libraries 中添加如图所示
![20211103104017](https://user-images.githubusercontent.com/15692322/140003044-3bf40fbf-2c45-4229-b508-2c14fbc040c8.jpg)

### 示例代码

在需要的地方添加

```Objective-C
#import <AVCodecSDK/AVCodecSDK.h>
```

初始化 AVTPlayerItem

```Objective-C
NSString* inPath = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"mp4"];
AVTPlayerItem *playerItem = [[AVTPlayerItem alloc] initWithURL:[NSURL fileURLWithPath:inPath]];
```

初始化 PLPlayer

```Objective-C
//初始化CGAVPlayer, CGAVPlayer必须是实例属性, 不可设置为局部变量, 否则播放器会被销毁
_player = [[CGAVPlayer alloc] initWithPlayerItem:playerItem];

//开启渲染, 否则只有声音
_player.enableRender = YES; 

// 设定代理
_player.delegate = self;
```

获取播放器的视频输出的 UIView 对象并添加为到当前 UIView 对象的 Subview

```Objective-C
//获取视频输出视图并添加为到当前 UIView 对象的 Subview
_playerLayer = [_player playerLayerWithFrame:CGRectMake(0, 100, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.width)];
[self.view.layer addSublayer:_playerLayer];
```

开始／暂停操作

```Objective-C

// 播放
[self.player play];

// 停止
[self.player stop];

// 暂停
[self.player pause];

// 继续播放
[self.player resume];
```

播放器状态获取, 更多回调查看CGPlayerDelegate
```Objective-C
// 实现 <CGPlayerDelegate> 来控制流状态的变更
- (void)player:(nonnull CGAVPlayer *)player statusChanged:(CGPlayerStatus)status {
    // 这里会返回流的各种状态，你可以根据状态做 UI 定制及各类其他业务操作
    // 除了 Error 状态，其他状态都会回调这个方法
    // 第一帧渲染后，将收到第一个 CGPlayerStatusReady 状态
    // 播放过程中，将收到 CGPlayerStatusPlaying 状态
}

- (void)player:(nonnull CGAVPlayer *)player stoppedWithError:(nullable NSError *)error {
    // 当发生错误，停止播放时，会回调这个方法
}

- (void)player:(nonnull CGAVPlayer *)player progress:(int64_t)progress {
    // 进度回调
}

- (void)player:(nonnull CGAVPlayer *)player firstRender:(AVTPlayerFirstRenderType)firstRenderType {
    // 首帧渲染的回调
}

- (void)player:(nonnull CGAVPlayer *)player seekToCompleted:(BOOL)isCompleted {
    // seek完成的通知
}
```

## 视频帧回调输出
AVPlayerVideoOutput是一个输出类, 实现代理方法可获取 播放/seek 过程中的每一帧回调数据

### 代码示例
初始化输出文件配置
```Objective-C
NSDictionary *outputSettings = @{kPixelBufferPixelFormatTypeKey: @(kPixelFormatType_32BGRA)};
```

初始化 AVPlayerVideoOutput

```Objective-C
    
//初始化AVPlayerVideoOutput
AVPlayerVideoOutput *videoOutput = [[AVPlayerVideoOutput alloc] initWithOutputSettings:outputSettings];

//添加输出
[_player addVideoOutput:videoOutput];

//设置代理
videoOutput.outputDelegate = self;

```

```Objective-C

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

//失败
- (void)output:(nonnull AVPlayerVideoOutput *)output error:(NSError *)error;

```

## 版本历史
- 1.0.0
    - 发布第一个版本

## 版本规划
    支持点播

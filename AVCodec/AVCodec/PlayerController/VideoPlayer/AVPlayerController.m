//
//  AVTPlayerController.m
//  AVPlayer
//
//  Created by AVPlayer on 2021/5/8.
//

#import "AVPlayerController.h"
#import <AVCodecSDK/AVCodecSDK.h>
#import "AVPlayerView.h"

@interface AVPlayerController ()<CGPlayerDelegate, CGPlayerVideoOutputDelegate, CGPlayerViewDelegate, CGVideoCompositing>
@property(nonatomic, strong)CGAVPlayer *player;
@property(nonatomic, strong)AVTPlayerItem *playerItem;
@property(nonatomic, strong)AVTPlayerLayer *playerLayer;
@property(nonatomic, strong)AVPlayerView *playerView;
@end

@implementation AVPlayerController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.darkGrayColor;
        
    NSString* inPath = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"mp4"];
    _playerItem = [[AVTPlayerItem alloc] initWithURL:[NSURL fileURLWithPath:inPath]];
    _player = [[CGAVPlayer alloc] initWithPlayerItem:_playerItem];
    _player.enableRender = YES;
    _player.delegate = self;
    _playerLayer = [_player playerLayerWithFrame:CGRectMake(0, 100, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.width)];
//    _playerLayer.position = self.view.layer.position;
    [self.view.layer addSublayer:_playerLayer];

    NSDictionary *outputSettings = @{kPixelBufferPixelFormatTypeKey: @(kPixelFormatType_32BGRA)};
    AVPlayerVideoOutput *videoOutput = [[AVPlayerVideoOutput alloc] initWithOutputSettings:outputSettings];
    [_player addVideoOutput:videoOutput];
    videoOutput.outputDelegate = self;
    
    AVPlayerVideoComposition *composition = [[AVPlayerVideoComposition alloc] init];
    composition.videoCompositing = self;
    _player.videoComposition = composition;
    
    //UI 交互
    _playerView = [[AVPlayerView alloc] initWithFrame:CGRectMake(0, 100, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height - 100)];
    _playerView.delegate = self;
    [self.view addSubview:_playerView];
}

#pragma mark -
#pragma mark AVPlayerViewDelegate
- (void)playerSeekStart:(AVPlayerView *)playerView {
    [_player holdSeek:YES];
}

- (void)playerSeekChanged:(AVPlayerView *)playerView progress:(CGFloat)progress {
    CGFloat pts = progress * _player.playerItem.duration;
    [_player seekTo:CMTimeMake(pts, 1)];
}

- (void)playerSeekEnd:(AVPlayerView *)playerView {
    [_player holdSeek:NO];
}

- (void)playerStatusToggle:(AVPlayerView *)playerView isPlay:(BOOL)isPlay {
    if (self.player.status == CGPlayerStatusReady) {
        [self.player play];
    } else if (self.player.status == CGPlayerStatusPaused) {
        [self.player resume];
    } else if (self.player.status == CGPlayerStatusPlaying) {
        [self.player pause];
    }
}

- (void)playerRateChanged:(AVPlayerView *)playerView rate:(CGFloat)rate {
    _player.playSpeed = rate;
}

#pragma mark -
#pragma mark AVTAVPlayerDelegate
- (void)player:(CGAVPlayer *)player progress:(int64_t)progress {
    _playerView.progress = (CGFloat)progress / _player.playerItem.duration;
    [_playerView updatePlayTime:progress totalTime:_player.playerItem.duration];
}

- (void)player:(CGAVPlayer *)sender onError:(NSInteger)errorCode {
    
}

- (void)player:(CGAVPlayer *)player statusChanged:(CGPlayerStatus)status {
    if (status == CGPlayerStatusPlaying) {
        [_playerView setIsPlay:YES];
    } else if (status == CGPlayerStatusPaused) {
        [_playerView setIsPlay:NO];
    } else if (status == CGPlayerStatusResumed) {
        [_playerView setIsPlay:YES];
    }
}

- (void)player:(CGAVPlayer *)player seekToCompleted:(BOOL)isCompleted {
    NSLog(@"seekToCompleted: %@", isCompleted ? @"YES" : @"NO");
}

#pragma mark -
#pragma mark AVPlayerVideoOutputDelegate
- (void)output:(AVPlayerVideoOutput *)output willRenderFrame:(CVPixelBufferRef)frame pts:(int64_t)pts {
    
}

- (void)output:(AVPlayerVideoOutput *)output willRenderBuffer:(UInt8 *)buffer pts:(int64_t)pts width:(NSInteger)width height:(NSInteger)height {
    
}

#pragma mark -
#pragma mark CGVideoCompositing
- (void)startVideoCompositionRequest:(AVPlayerVideoComposition *)asyncVideoCompositionRequest willRenderBuffer:(UInt8 *)buffer pts:(int64_t)pts width:(NSInteger)width height:(NSInteger)height {
    
}

- (void)startVideoCompositionRequest:(AVPlayerVideoComposition *)asyncVideoCompositionRequest willRenderFrame:(CVPixelBufferRef)frame pts:(int64_t)pts {
    [asyncVideoCompositionRequest finishWithComposedVideoFrame:frame];
}

@end

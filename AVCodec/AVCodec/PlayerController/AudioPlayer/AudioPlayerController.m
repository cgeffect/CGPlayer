//
//  AudioPlayerController.m
//  AVCodec
//
//  Created by Jason on 2021/10/13.
//

#import "AudioPlayerController.h"
#import <AVCodecSDK/AVCodecSDK.h>
#import "AVAudioPlayerView.h"

@interface AudioPlayerController ()<CGPlayerViewDelegate, AVTAudioPlayerDelegate>
{
    AVTAudioPlayer *_audioPlayer;
    float _seekPos;
}
@property(nonatomic, strong)AVAudioPlayerView *playerView;
@end

@implementation AudioPlayerController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.darkGrayColor;
    //UI 交互
    _playerView = [[AVAudioPlayerView alloc] initWithFrame:CGRectMake(0, 400, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height - 100)];
    _playerView.delegate = self;
    [self.view addSubview:_playerView];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"aac"];
    _audioPlayer = [AVTAudioPlayer sharePlayer];
//    _audioPlayer.pcmPath = [self creatFile:@".pcm"];
    [_audioPlayer loadWithURL:path];
    _audioPlayer.delegate = self;
    
}

#pragma mark -
#pragma mark AVPlayerViewDelegate
- (void)playerSeekStart:(AVAudioPlayerView *)playerView {
    [_audioPlayer holdSeek:YES];
}

- (void)playerSeekChanged:(AVAudioPlayerView *)playerView progress:(CGFloat)progress {
    _seekPos = progress;
}

- (void)playerSeekEnd:(AVAudioPlayerView *)playerView {
    CGFloat pts = _seekPos * _audioPlayer.durationMs;
    [_audioPlayer seekTo:pts];
    [_audioPlayer holdSeek:NO];
}

- (void)playerStatusToggle:(AVAudioPlayerView *)playerView isPlay:(BOOL)isPlay {
    if (_audioPlayer.status == AVTAudioPlayerStatusReady) {
        [_audioPlayer play];
    } else if (_audioPlayer.status == AVTAudioPlayerStatusPaused) {
        [_audioPlayer resume];
    } else if (_audioPlayer.status == AVTAudioPlayerStatusPlaying) {
        [_audioPlayer pause];
    } else if (_audioPlayer.status == AVTAudioPlayerStatusResumed) {
        [_audioPlayer pause];
    }
}

- (void)playerRateChanged:(AVAudioPlayerView *)playerView rate:(CGFloat)rate {
}

#pragma mark - AVTAudioPlayerDelegate
- (void)player:(AVTAudioPlayer *)player progress:(int64_t)progress {
    _playerView.progress = (CGFloat)progress / _audioPlayer.durationMs;
    [_playerView updatePlayTime:progress totalTime:_audioPlayer.durationMs];

}

- (void)player:(AVTAudioPlayer *)player statusChanged:(AVTAudioPlayerStatus)status {
    if (status == CGPlayerStatusPlaying) {
        [_playerView setIsPlay:YES];
    } else if (status == CGPlayerStatusPaused) {
        [_playerView setIsPlay:NO];
    } else if (status == CGPlayerStatusResumed) {
        [_playerView setIsPlay:YES];
    }
}

- (NSString *)creatFile:(NSString *)fileName {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *path = [paths objectAtIndex:0];
    NSString *tmpPath = [path stringByAppendingPathComponent:@"temp"];
    NSTimeInterval time = [[NSDate date] timeIntervalSince1970];
    [[NSFileManager defaultManager] createDirectoryAtPath:tmpPath withIntermediateDirectories:YES attributes:nil error:NULL];
    NSString* outFilePath = [tmpPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%d_%@", (int)time, fileName]];
    return outFilePath;
}

@end

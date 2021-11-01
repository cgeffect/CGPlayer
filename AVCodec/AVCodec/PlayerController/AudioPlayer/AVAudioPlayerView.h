//
//  AVAudioPlayerView.h
//  AVCodec
//
//  Created by Jason on 2021/10/19.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioPlayerView;
@protocol CGPlayerViewDelegate <NSObject>

- (void)playerSeekStart:(AVAudioPlayerView *)playerView;

- (void)playerSeekChanged:(AVAudioPlayerView *)playerView progress:(CGFloat)progress;

- (void)playerSeekEnd:(AVAudioPlayerView *)playerView;

- (void)playerStatusToggle:(AVAudioPlayerView *)playerView isPlay:(BOOL)isPlay;

- (void)playerRateChanged:(AVAudioPlayerView *)playerView rate:(CGFloat)rate;

@end

@interface AVAudioPlayerView : UIView

@property (nonatomic, weak) id<CGPlayerViewDelegate> delegate;

@property (nonatomic, assign) CGFloat progress;

- (void)updatePlayTime:(int64_t)playTime totalTime:(int64_t)totalTime;

- (void)setIsPlay:(BOOL)isPlay;
@end

NS_ASSUME_NONNULL_END

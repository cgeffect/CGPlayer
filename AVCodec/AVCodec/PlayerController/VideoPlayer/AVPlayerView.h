//
//  AVTPlayerView.h
//  AVPlayer
//
//  Created by AVPlayer on 2021/5/11.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPlayerView;
@protocol CGPlayerViewDelegate <NSObject>

- (void)playerSeekStart:(AVPlayerView *)playerView;

- (void)playerSeekChanged:(AVPlayerView *)playerView progress:(CGFloat)progress;

- (void)playerSeekEnd:(AVPlayerView *)playerView;

- (void)playerStatusToggle:(AVPlayerView *)playerView isPlay:(BOOL)isPlay;

- (void)playerRateChanged:(AVPlayerView *)playerView rate:(CGFloat)rate;

@end

@interface AVPlayerView : UIView

@property (nonatomic, weak) id<CGPlayerViewDelegate> delegate;

@property (nonatomic, assign) CGFloat progress;

- (void)updatePlayTime:(int64_t)playTime totalTime:(int64_t)totalTime;

- (void)setIsPlay:(BOOL)isPlay;
@end

typedef enum : NSUInteger {
    PLPlayerRatioDefault,
    PLPlayerRatioFullScreen,
    PLPlayerRatio16x9,
    PLPlayerRatio4x3,
} PLPlayerRatio;

NS_ASSUME_NONNULL_END

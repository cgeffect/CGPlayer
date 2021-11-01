//
//  AVTPlayerView.m
//  AVPlayer
//
//  Created by AVPlayer on 2021/5/11.
//

#import "AVPlayerView.h"
#import <AVCodecSDK/AVCodecSDK.h>
#import <CoreGraphics/CoreGraphics.h>
#import "AVControlView.h"
#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

@interface AVPlayerView ()<UIGestureRecognizerDelegate, AVControlViewDelegate>
{
    int64_t _totalTime;
}

@property (nonatomic, strong) UIView *bottomBarView;
@property (nonatomic, strong) UISlider *slider;
@property (nonatomic, strong) UIView *gestureView;
@property (nonatomic, strong) UILabel *playTimeLabel;
@property (nonatomic, strong) UILabel *durationLabel;
@property (nonatomic, strong) UIButton *playButton;
@property (nonatomic, strong) UIButton *snapshotButton;

@property (nonatomic, strong) AVControlView *controlView;
@end

@implementation AVPlayerView
- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self initBottomBar];
        [self initControlView];
    }
    return self;
}
- (void)initControlView {
    _controlView = [[AVControlView alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(self.bottomBarView.frame), self.frame.size.width, 100)];
    _controlView.backgroundColor = [UIColor.blackColor colorWithAlphaComponent:0.3];
    [self addSubview:_controlView];
    _controlView.delegate = self;
}
- (void)initBottomBar {
    
    self.bottomBarView = [[UIView alloc] init];
    self.bottomBarView.frame = CGRectMake(0, self.bounds.size.width, self.bounds.size.width, 50);
    
    self.playButton = [UIButton buttonWithType:(UIButtonTypeCustom)];
    [self.playButton setTintColor:[UIColor whiteColor]];
    [self.playButton setImage:[UIImage imageNamed:@"player_pause"] forState:(UIControlStateNormal)];
    [self.playButton setImage:[UIImage imageNamed:@"player_play"] forState:(UIControlStateSelected)];
    [self.playButton addTarget:self action:@selector(clickPlayButton:) forControlEvents:(UIControlEventTouchUpInside)];
    self.playButton.frame = CGRectMake(0, 5, 40, 40);
    
    self.playTimeLabel = [[UILabel alloc] init];
    self.playTimeLabel.font = [UIFont systemFontOfSize:12];
    self.playTimeLabel.textColor = [UIColor whiteColor];
    self.playTimeLabel.text = @"00:00:00";
    [self.playTimeLabel sizeToFit];
    self.playTimeLabel.frame = CGRectMake(CGRectGetMaxX(self.playButton.frame), 0, 65, 50);
    
    self.slider = [[UISlider alloc] init];
    self.slider.maximumValue = 1;
    self.slider.minimumValue = 0;
    self.slider.continuous = NO;
    [self.slider setThumbImage:[UIImage imageNamed:@"slider_thumb"] forState:(UIControlStateNormal)];
    self.slider.maximumTrackTintColor = [UIColor whiteColor];
    self.slider.minimumTrackTintColor = [UIColor colorWithRed:.2 green:.2 blue:.8 alpha:1];
    self.slider.frame = CGRectMake(CGRectGetMaxX(self.playTimeLabel.frame), 0, self.bounds.size.width - 180, 50);
    
    self.gestureView = [[UIView alloc] initWithFrame:self.slider.bounds];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onGestureEvent:)];
    [self.gestureView addGestureRecognizer:tap];
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(onGestureEvent:)];
    [self.gestureView addGestureRecognizer:pan];
    [self.slider addSubview:self.gestureView];
    
    self.durationLabel = [[UILabel alloc] init];
    self.durationLabel.font = [UIFont systemFontOfSize:12];
    self.durationLabel.textColor = [UIColor whiteColor];
    self.durationLabel.text = @"00:00:00";
    [self.durationLabel sizeToFit];
    self.durationLabel.frame = CGRectMake(CGRectGetMaxX(self.slider.frame) + 5, 0, 65, 50);

    [self addSubview:self.bottomBarView];
    [self.bottomBarView addSubview:self.playButton];
    [self.bottomBarView addSubview:self.playTimeLabel];
    [self.bottomBarView addSubview:self.durationLabel];
    [self.bottomBarView addSubview:self.slider];
}

- (void)onGestureEvent:(UIGestureRecognizer *)gesture {
    if ([gesture isKindOfClass:[UIPanGestureRecognizer class]]) {
        switch (gesture.state) {
            case UIGestureRecognizerStateBegan:
                [self slideValueChangedBegin];
                break;
            case UIGestureRecognizerStateChanged: {
                CGPoint point = [gesture locationInView:gesture.view];
                [self updateIndicatorPos:point.x];
                [self sliderValueChange:_progress];
            }
                break;
            case UIGestureRecognizerStateEnded:
                [self slideValueChangedEnd];
                break;
            case UIGestureRecognizerStateCancelled:
                [self slideValueChangedEnd];
                break;
            case UIGestureRecognizerStateFailed:
                [self slideValueChangedEnd];
                break;
            default:
                break;
        }
    } else if ([gesture isKindOfClass:[UITapGestureRecognizer class]]) {
        [self slideValueChangedBegin];
        CGPoint point = [gesture locationInView:gesture.view];
        [self updateIndicatorPos:point.x];
        [self sliderValueChange:_progress];
        [self slideValueChangedEnd];
    }
}

- (void)slideValueChangedBegin {
    [self.delegate playerSeekStart:self];
}

- (void)sliderValueChange:(CGFloat)progress {
    self.slider.value = progress;
    [self.delegate playerSeekChanged:self progress:progress];
    [self updatePlayTime:progress * _totalTime totalTime:_totalTime];
}

- (void)slideValueChangedEnd {
    [self.delegate playerSeekEnd:self];
}

- (CGFloat)updateIndicatorPos:(CGFloat)transX {
    CGFloat x = MAX(0, MIN(self.slider.bounds.size.width, transX));
    _progress = x / self.slider.bounds.size.width;
    if (_progress < 0 || _progress > 1) {
        return 0;;
    }
    return _progress;
}

- (void)setProgress:(CGFloat)progress {
    _progress = progress;
    self.slider.value = progress;
}

- (void)updatePlayTime:(int64_t)playTime totalTime:(int64_t)totalTime {
    _totalTime = totalTime;
    {
        CGFloat fduration = playTime / 1000.0;
        int duration = fduration;
//        int hour = duration / 3600;
        int min  = (duration % 3600) / 60;
        int sec  = duration % 60;
        int ms   = playTime % 1000;
        self.playTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d:%03d", min, sec, ms];
    }
    {
        CGFloat fduration = totalTime / 1000.0;
        int duration = fduration;
//        int hour = duration / 3600;
        int min  = (duration % 3600) / 60;
        int sec  = duration % 60;
        int ms   = totalTime % 1000;
        self.durationLabel.text = [NSString stringWithFormat:@"%02d:%02d:%03d", min, sec, ms];
    }
}

- (void)setIsPlay:(BOOL)isPlay {
    _playButton.selected = isPlay;
}

- (void)clickPlayButton:(UIButton *)btn {
    btn.selected = !btn.isSelected;
    [self.delegate playerStatusToggle:self isPlay:btn.isSelected];
}

- (void)resetUI {
    self.slider.value = 0;
    self.playTimeLabel.text = @"0:00:00";
    self.durationLabel.text = @"0:00:00";
}

- (void)didRateChange:(CGFloat)rate {
    [self.delegate playerRateChanged:self rate:rate];
}
-(void)dealloc {
}

@end

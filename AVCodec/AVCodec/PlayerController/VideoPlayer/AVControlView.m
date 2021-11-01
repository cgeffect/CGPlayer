//
//  AVControlView.m
//  AVCodec
//
//  Created by Jason on 2021/10/11.
//

#import "AVControlView.h"


@interface AVControlView ()
{
    NSArray *_rateList;
    NSMutableArray *_rateListBtn;
}
@end

@implementation AVControlView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        _rateList = @[@"0.5", @"0.75", @"1.0", @"1.25", @"1.5", @"2.0"];
        _rateListBtn = [NSMutableArray array];
        [self setupUI];
    }
    return self;
}

- (void)setupUI {
    UILabel *rateLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 50, 40)];
    rateLabel.text = @"倍速";
    rateLabel.textColor = UIColor.whiteColor;
    rateLabel.textAlignment = NSTextAlignmentCenter;
    [self addSubview:rateLabel];
    
    for (int i = 0; i < _rateList.count; i++) {
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        [self addSubview:btn];
        [btn addTarget:self action:@selector(rateAction:) forControlEvents:UIControlEventTouchUpInside];
        btn.tag = i;
        btn.frame = CGRectMake(i * 50, CGRectGetMaxY(rateLabel.frame), 50, 40);
        [btn setTitle:_rateList[i] forState:UIControlStateNormal];
        [btn setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [btn setTitleColor:UIColor.orangeColor forState:UIControlStateSelected];
        [_rateListBtn addObject:btn];
        if (i == 2) {
            btn.selected = YES;
        }
    }
}

- (void)rateAction:(UIButton *)btn {
    for (UIButton *btn in _rateListBtn) {
        btn.selected = NO;
    }
    btn.selected = YES;
    NSString *rate = _rateList[btn.tag];
    [self.delegate didRateChange:rate.floatValue];
}
@end

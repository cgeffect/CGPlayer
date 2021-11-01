//
//  AVControlView.h
//  AVCodec
//
//  Created by Jason on 2021/10/11.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVControlViewDelegate <NSObject>

- (void)didRateChange:(CGFloat)rate;

@end

@interface AVControlView : UIView
@property(nonatomic, weak)id<AVControlViewDelegate>delegate;
@end

NS_ASSUME_NONNULL_END

//
//  AVTPlayerLayer.h
//  CGPlayer
//
//  Created by Jason on 2021/4/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@import QuartzCore;
#define AVTF_EXPORT extern
typedef NSString * CGLayerVideoGravity NS_STRING_ENUM;
AVTF_EXPORT CGLayerVideoGravity const CGLayerVideoGravityResizeAspect;
AVTF_EXPORT CGLayerVideoGravity const CGLayerVideoGravityResizeAspectFill;
AVTF_EXPORT CGLayerVideoGravity const CGLayerVideoGravityResize;

@interface AVTPlayerLayer : CALayer {
@private

}

@property(copy) CGLayerVideoGravity videoGravity;

@property(nonatomic, readonly, getter=isReadyForDisplay) BOOL readyForDisplay;

@property (nonatomic, readonly) CGRect videoRect;

@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *pixelBufferAttributes;

@end

NS_ASSUME_NONNULL_END

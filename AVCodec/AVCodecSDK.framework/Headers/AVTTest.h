//
//  AVTTest.h
//  AVTPlayer
//
//  Created by Jason on 2021/4/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AVTTest : NSObject

- (void)UFAudioDecodeAT:(NSString *)path aOut:(NSString *)aOut vOut:(NSString *)vOut;

- (void)AVTAudioQueueCapture:(NSString *)path;

- (void)AVTAudioUnitCapture:(NSString *)path;

- (void)AVTAudioUnitRender:(NSString *)path;

- (void)AVTAudioQueueRender:(NSString *)path;

- (void)start;

/*
 属性设置readonly, 但是实现了该属性的setter方法, 外界依然可以使用点语法复赋值
 */
@property(nonatomic, assign, readonly)int test;
- (void)setTest:(int)a;
@end

NS_ASSUME_NONNULL_END

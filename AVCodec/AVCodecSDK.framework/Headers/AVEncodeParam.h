//
//  AVEncodeParam.h
//  AVCodecSDK
//
//  Created by Jason on 2021/8/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AVEncodeParam : NSObject
@property(nonatomic, strong) NSString *savePath;
@property(nonatomic, assign) int srcWidth;
@property(nonatomic, assign) int srcHeight;
@property(nonatomic, assign) int frameRate; //帧率, 一秒钟多少帧
@property(nonatomic, assign) int maxFrameCount;

@end

NS_ASSUME_NONNULL_END

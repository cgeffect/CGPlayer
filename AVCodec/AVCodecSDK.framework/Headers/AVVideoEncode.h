//
//  AVVideoEncode.h
//  AVCodecSDK
//
//  Created by Jason on 2021/8/25.
//

#import <Foundation/Foundation.h>
#import <AVCodecSDK/AVEncodeParam.h>
#import <AVCodecSDK/AVVideoFrame.h>

NS_ASSUME_NONNULL_BEGIN

@class AVVideoEncode;
@protocol AVVideoEncodeDelegate <NSObject>
@optional
- (void)encodeOnStart:(AVVideoEncode *)videoEncoder;

- (void)videoEncoder:(AVVideoEncode *)videoEncoder onProgress:(float)progress;

- (void)videoEncoder:(AVVideoEncode *)videoEncoder onFinish:(NSString *)filePath;

- (void)videoEncoder:(AVVideoEncode *)videoEncoder onError:(NSInteger)errorCode;

@end

@interface AVVideoEncode : NSObject

@property(nonatomic, weak) id <AVVideoEncodeDelegate> delegate;

- (void)startEncode:(AVEncodeParam *)param;

- (void)stopEncode;

- (void)addVideoFrame:(AVVideoFrame *)videoFrame;

- (void)glInit;

- (void)glUnInit;

- (void)destroy;

@end

NS_ASSUME_NONNULL_END

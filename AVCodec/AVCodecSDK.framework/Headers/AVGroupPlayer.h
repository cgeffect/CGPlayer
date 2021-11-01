//
//  AVComboPlayer.h
//  CGCodecSDK
//
//  Created by Jason on 2021/8/17.
//

#import <Foundation/Foundation.h>
#import <AVCodecSDK/AVTPlayerItem.h>
#import <AVCodecSDK/CGAVPlayer.h>
#import <AVCodecSDK/AVVideoFrame.h>

NS_ASSUME_NONNULL_BEGIN

@class AVGroupPlayer;
@protocol AVComboDelegate <NSObject>

- (void)player:(nonnull AVGroupPlayer *)sender statusChanged:(CGPlayerStatus)status;

- (void)player:(nonnull AVGroupPlayer *)sender willRenderBuffer:(nullable NSArray <AVVideoFrame *> *)bufferList pts:(uint64_t)pts;

- (void)player:(AVGroupPlayer *)sender onProgress:(float)progress;

- (void)player:(AVGroupPlayer *)player seekToCompleted:(BOOL)isCompleted;

@end

@interface AVGroupPlayer : NSObject

@property (nonatomic, weak) id<AVComboDelegate>delegate;

- (instancetype)initWithItems:(NSArray <AVTPlayerItem *>*)items;

@property (nonatomic, readonly) CGPlayerStatus status;

@property (nonatomic, readonly) int64_t duration;

@property (nonatomic, assign, readonly) int64_t startTime;

@property (nonatomic, assign, readonly) int64_t endTime;

- (void)play;

- (void)pause;

- (void)resume;

- (void)stop;

- (void)holdSeek:(BOOL)isSeek;

- (void)seekTo:(float)ptsMs;

- (void)destroy;

@end

NS_ASSUME_NONNULL_END

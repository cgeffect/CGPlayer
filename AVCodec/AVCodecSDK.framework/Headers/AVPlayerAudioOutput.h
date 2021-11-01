//
//  CGPlayerAudioOutput.h
//  CGPlayer
//
//  Created by Jason on 2021/5/11.
//

#import <Foundation/Foundation.h>
@import AVFoundation;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief 音频采样格式
 
 @since v1.0.0
 */
typedef NS_ENUM(NSInteger, CGPlayerAVSampleFormat) {
    CGAVPlayerAV_SAMPLE_FMT_NONE = -1,
    CGAVPlayerAV_SAMPLE_FMT_U8,          ///< unsigned 8 bits
    CGAVPlayerAV_SAMPLE_FMT_S16,         ///< signed 16 bits
    CGAVPlayerAV_SAMPLE_FMT_S32,         ///< signed 32 bits
    CGAVPlayerAV_SAMPLE_FMT_FLT,         ///< float
    CGAVPlayerAV_SAMPLE_FMT_DBL,         ///< double
    
    CGAVPlayerAV_SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
    CGAVPlayerAV_SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
    CGAVPlayerAV_SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
    CGAVPlayerAV_SAMPLE_FMT_FLTP,        ///< float, planar
    CGAVPlayerAV_SAMPLE_FMT_DBLP,        ///< double, planar
    
    CGAVPlayerAV_SAMPLE_FMT_NB           ///< Number of sample formats. DO NOT USE if linking dynamically
};

@class AVPlayerAudioOutput;
@protocol CGPlayerAudioOutputDelegate <NSObject>
@optional

/**
 回调音频数据
 
 @param player 调用该方法的 AVTAVPlayer 对象
 @param audioBufferList 音频数据
 @param audioStreamDescription 音频格式信息
 @param pts 显示时间戳 是解码器进行显示帧时相对于SCR（系统参考）的时间戳。SCR可以理解为解码器应该开始从磁盘读取数据时的时间
 @param sampleFormat 采样位数 枚举：CGAVPlayerAVSampleFormat
 @return audioBufferList 音频数据
 
 @since v1.0.0
 */
- (nonnull AudioBufferList *)player:(nonnull AVPlayerAudioOutput *)player willAudioRenderBuffer:(nonnull AudioBufferList *)audioBufferList asbd:(AudioStreamBasicDescription)audioStreamDescription pts:(int64_t)pts sampleFormat:(CGPlayerAVSampleFormat)sampleFormat;

- (void)output:(nonnull AVPlayerAudioOutput *)output error:(NSError *)error;

@end

@interface AVPlayerAudioOutput : NSObject

- (instancetype)initWithOutputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings;

@property (nonatomic, weak) id<CGPlayerAudioOutputDelegate>outputDelegate;

@end

NS_ASSUME_NONNULL_END

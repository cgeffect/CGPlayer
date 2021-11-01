//
//  AVTAudioFormat.h
//  AVTPlayer
//
//  Created by Jason on 2021/4/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef UInt32  AVTAudioFormatID;
typedef UInt32  AVTAudioFormatFlags;
struct AVTAudioStreamBasicDescription
{
    Float64             mSampleRate;
    AVTAudioFormatID    mFormatID;
    AVTAudioFormatFlags mFormatFlags;
    UInt32              mBytesPerPacket;
    UInt32              mFramesPerPacket;
    UInt32              mBytesPerFrame;
    UInt32              mChannelsPerFrame;
    UInt32              mBitsPerChannel;
    UInt32              mReserved;
};
typedef struct AVTAudioStreamBasicDescription  AVTAudioStreamBasicDescription;

@interface AVTAudioFormat : NSObject {
@public
    AVTAudioStreamBasicDescription _asbd;
}
@end

NS_ASSUME_NONNULL_END

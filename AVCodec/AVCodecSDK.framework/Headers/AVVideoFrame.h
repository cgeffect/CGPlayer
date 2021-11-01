//
//  CGVideoFrame.h
//  CGCodecSDK
//
//  Created by 王腾飞 on 2021/8/18.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AVVideoFrame : NSObject
@property(nonatomic, assign) UInt8 *data;
@property(nonatomic, assign) int width;
@property(nonatomic, assign) int height;
@property(nonatomic, assign) int length;
@property(nonatomic, assign) float pts;
@property(nonatomic, assign) BOOL index;
@end

@interface AVVideoFrameTex : AVVideoFrame
@property(nonatomic, assign) int texId;
@end

NS_ASSUME_NONNULL_END

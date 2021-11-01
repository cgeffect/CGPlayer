//
//  CGAssetReader.h
//  CGCodecSDK
//
//  Created by 王腾飞 on 2021/7/26.
//

#import <Foundation/Foundation.h>
@import CoreVideo;
@import UIKit;
@import CoreGraphics;
NS_ASSUME_NONNULL_BEGIN

@interface AVAssetReaderAV : NSObject

- (instancetype)initWithSync:(BOOL)isSync;

@property (nonatomic, assign, readonly) int64_t totalDuration;

- (void)loadResource:(NSString *)filePath;

- (void)readPixelBuffer:(void(^)(_Nullable CVPixelBufferRef pixelBuffer,
                                 NSInteger index, float frameTimeMs))processHandler
                            finishHandler:(void(^)(void))finishHandler
                            cancelHnadler:(void(^)(void))cancelHander;

- (void)readImage:(void(^)(UIImage * _Nullable image,
                           NSInteger index, float frameTimeMs))processHandler
                            finishHandler:(void(^)(void))finishHandler
                            cancelHnadler:(void(^)(void))cancelHander;

- (void)readPixelData:(void(^)( UInt8 * _Nullable data, CGSize size,
                                 NSInteger index, float frameTimeMs))processHandler
                            finishHandler:(void(^)(void))finishHandler
                            cancelHnadler:(void(^)(void))cancelHander;
@end

NS_ASSUME_NONNULL_END

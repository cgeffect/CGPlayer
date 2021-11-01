//
//  AVAssetReaderVT.h
//  AVCodecSDK
//
//  Created by 王腾飞 on 2021/8/29.
//

#import <Foundation/Foundation.h>
@import CoreVideo;
@import UIKit;
@import CoreGraphics;

NS_ASSUME_NONNULL_BEGIN

@interface AVAssetReaderVT : NSObject

//YES 异步返回,AVAssetReaderVT对象必须是全局变量
- (instancetype)initWithSync:(BOOL)isSync;

@property (nonatomic, assign, readonly) int64_t totalDuration;

- (void)loadResource:(NSString *)filePath;

- (void)readPixelBuffer:(NSArray <NSNumber *>*)ptsList
         processHandler:(void(^)(_Nullable CVPixelBufferRef pixelBuffer,
                                 NSInteger index, float frameTimeMs))processHandler
                            finishHandler:(void(^)(void))finishHandler
                            cancelHnadler:(void(^)(void))cancelHander;

- (void)readImage:(NSArray <NSNumber *>*)ptsList
   processHandler:(void(^)(UIImage * _Nullable image,
                           NSInteger index, float frameTimeMs))processHandler
                            finishHandler:(void(^)(void))finishHandler
                            cancelHnadler:(void(^)(void))cancelHander;

@end

NS_ASSUME_NONNULL_END

//
// Created by 12418 on 2019/10/29.
//

#include <android/log.h>
#include "SoundRecording.h"

int32_t SoundRecording::write(const float *sourceData, int32_t numSamples) {
    //写之前先判断剩余容量是否充足
    if (mWriteIndex + numSamples > kMaxSamples){
        numSamples = kMaxSamples - mWriteIndex;
    }

    for (int i = 0; i < numSamples; ++i) {
        mData[mWriteIndex++] = sourceData[i];
    }

    return numSamples;
}

int32_t SoundRecording::read(float *targetData, int32_t numSamples) {
    int32_t framesRead = 0;
    while (framesRead < numSamples && mReadIndex < mWriteIndex){
        targetData[framesRead++] = mData[mReadIndex++];
        if (mIsLooping && mReadIndex == mWriteIndex) mReadIndex = 0;
    }
    return framesRead;
}
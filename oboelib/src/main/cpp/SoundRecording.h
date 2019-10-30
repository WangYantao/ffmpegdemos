//
// Created by 12418 on 2019/10/29.
//

#ifndef NDKDEMO_SOUNDRECORDING_H
#define NDKDEMO_SOUNDRECORDING_H

#include <cstdint>
#include <array>
#include <atomic>

#include "Definitions.h"

// 10s 48khz 的音频数据
constexpr int kMaxSamples = 480000;

class SoundRecording {
public:

    /**
     * 保存音频数据
     * @param sourceData 数据源（数组）
     * @param numSamples 要保存的采样数
     * @return 实际保存的采样数
     */
    int32_t write(const float *sourceData, int32_t numSamples);

    /**
     * 读取音频数据
     * @param targetData 目标数组（存放读取的音频数据）
     * @param numSamples 要读取的采样数
     * @return 实际读取的采样数
     */
    int32_t read(float *targetData, int32_t numSamples);
    bool isFull() const {
        return (mWriteIndex == kMaxSamples);
    };
    void setReadPositionToStart(){
        mReadIndex = 0;
    };
    void clear() { mWriteIndex = 0; };
    void setLooping(bool isLooping) { mIsLooping = isLooping; };
    int32_t getLength() const { return mWriteIndex; };
    static const int32_t getMaxSamples() { return kMaxSamples; };
private:
    std::atomic<int32_t> mWriteIndex { 0 };//位置索引（写）
    std::atomic<int32_t> mReadIndex { 0 };//位置索引（读）
    std::atomic<bool> mIsLooping { false };//循环标识符
    std::array<float,kMaxSamples> mData { 0 };//存放数据的数组
};


#endif //NDKDEMO_SOUNDRECORDING_H

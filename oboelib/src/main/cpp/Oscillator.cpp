//
// Created by 12418 on 2019/10/29.
//

#include "Oscillator.h"
#include <math.h>

#define TWO_PI (3.14158 * 2)
#define AMPLITUDE 0.3 //振幅
#define FREQUENCY 440.0

void Oscillator::setSampleRate(int32_t sampleRate) {
    phaseIncrement_ = (TWO_PI * FREQUENCY) / (double) sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Oscillator::render(float *audioData, int32_t numFrames) {
    if (!isWaveOn_.load()) phase_ = 0;

    for (int i = 0; i < numFrames; i++) {
        if (isWaveOn_.load()){
            //计算正弦波的下一个采样值
            audioData[i] = (float) (sin(phase_) * AMPLITUDE);
            //增加相位
            phase_ += phaseIncrement_;
            //处理周期
            if (phase_ > TWO_PI) phase_ -= TWO_PI;
        } else{
            //输出静音
            audioData[i] = 0;
        }
    }
}
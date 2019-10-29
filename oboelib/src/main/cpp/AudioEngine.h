//
// Created by 12418 on 2019/10/29.
//

#ifndef NDKDEMO_AUDIOENGINE_H
#define NDKDEMO_AUDIOENGINE_H

#include <aaudio/AAudio.h>
#include "Oscillator.h"

class AudioEngine {
public:
    bool start();
    void stop();
    void restart();
    void setToneOn(bool isToneOn);

private:
    Oscillator oscillator_;
    AAudioStream *stream_;
};


#endif //NDKDEMO_AUDIOENGINE_H

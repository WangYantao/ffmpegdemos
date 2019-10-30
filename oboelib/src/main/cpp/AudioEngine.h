//
// Created by 12418 on 2019/10/29.
//

#ifndef NDKDEMO_AUDIOENGINE_H
#define NDKDEMO_AUDIOENGINE_H

#include <cstdint>
#include <atomic>
#include <memory>
#include <aaudio/AAudio.h>
#include "SoundRecording.h"

class AudioEngine {
public:
    void start();
    void stop();
    void restart();
    aaudio_data_callback_result_t recordingCallback(float *audioData, int32_t numFrames);
    aaudio_data_callback_result_t playbackCallback(float *audioData, int32_t numFrames);
    void setRecording(bool isRecording);
    void setPlaying(bool isPlaying);
    void setLooping(bool isOn);

private:
    std::atomic<bool> mIsRecording = {false};
    std::atomic<bool> mIsPlaying = {false};
    SoundRecording mSoundRecording;
    AAudioStream* mPlaybackStream = nullptr;
    AAudioStream* mRecordingStream = nullptr;

    void stopStream(AAudioStream *stream) const;
    void closeStream(AAudioStream **stream) const;
};


#endif //NDKDEMO_AUDIOENGINE_H

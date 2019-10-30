//
// Created by 12418 on 2019/10/29.
//

#ifndef NDKDEMO_SOUNDRECORDINGUTILITIES_H
#define NDKDEMO_SOUNDRECORDINGUTILITIES_H

float convertInt16ToFloat(int16_t intValue);
void convertArrayInt16ToFloat(int16_t *source, float *target, int32_t length);
void fillArrayWithZeros(float *data, int32_t length);
void convertArrayMonoToStereo(float *data, int32_t numFrames);

#endif //NDKDEMO_SOUNDRECORDINGUTILITIES_H

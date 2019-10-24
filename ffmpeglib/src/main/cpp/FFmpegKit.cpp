//
// Created by 12418 on 2019/10/24.
//
#include <string>
#include "./include/com_demo_ffmpeglib_FFmpegKit.h"

extern "C" {

#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/imgutils.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#include "libx264/x264.h"

JNIEXPORT jstring JNICALL Java_com_demo_ffmpeglib_FFmpegKit_getFFmpegName
  (JNIEnv * env, jobject obj){
      return env->NewStringUTF(avcodec_configuration());
  }
}

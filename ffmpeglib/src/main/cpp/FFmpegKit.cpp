//
// Created by 12418 on 2019/10/24.
//
#include <string>
#include <jni.h>

extern "C" {

#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/imgutils.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#include "libx264/x264.h"
}

jstring getFFmpegName(JNIEnv *env, jobject obj){
    return env->NewStringUTF(avcodec_configuration());
}

//方法数组，正是这个，可以动态调用任意 native 方法
JNINativeMethod nativeMethods[] = {
        {"getFFmpegName", "()Ljava/lang/String;", (void *) getFFmpegName}
};

/********* 重写JNI_OnLoad方法,在loadLibrary("native-lib")动态注册FFmpegKit中的方法 ***********/
jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    jclass clz = env->FindClass("com/demo/ffmpeglib/FFmpegKit");

    env->RegisterNatives(clz, nativeMethods, sizeof(nativeMethods) / sizeof(nativeMethods[0]));

    return JNI_VERSION_1_4;
}
//
// Created by 12418 on 2019/10/24.
//
#include <string>
#include <jni.h>
#include <android/log.h>
#include "AudioEngine.h"

static AudioEngine audioEngine;

extern "C" {
}

jstring getOboeName(JNIEnv *env, jobject instance){
    return env->NewStringUTF("wangyt");
}

void startEngine(JNIEnv *env, jobject instance){
    audioEngine.start();
}

void stopEngine(JNIEnv *env, jobject instance){
    audioEngine.stop();
}

void setRecording(JNIEnv *env, jobject instance, jboolean isRecording){
    __android_log_print(ANDROID_LOG_DEBUG, "oboe-kit", "Recording? %d", isRecording);
    audioEngine.setRecording(isRecording);
}

void setPlaying(JNIEnv *env, jobject instance, jboolean isPlaying){
    __android_log_print(ANDROID_LOG_DEBUG, "oboe-kit", "Playing? %d", isPlaying);
    audioEngine.setPlaying(isPlaying);
}

void setLooping(JNIEnv *env, jobject instance, jboolean isOn){
    audioEngine.setLooping(isOn);
}

//方法数组，正是这个，可以动态调用任意 native 方法
JNINativeMethod nativeMethods[] = {
        {"getOboeName", "()Ljava/lang/String;", (void *) getOboeName},
        {"startEngine", "()V", (void *) startEngine},
        {"stopEngine", "()V", (void *) stopEngine},
        {"setRecording", "(Z)V", (void *) setRecording},
        {"setPlaying", "(Z)V", (void *) setPlaying},
        {"setLooping", "(Z)V", (void *) setLooping}
};

/********* 重写JNI_OnLoad方法,在loadLibrary("native-lib")动态注册FFmpegKit中的方法 ***********/
jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    jclass clz = env->FindClass("com/demo/oboelib/OboeKit");

    env->RegisterNatives(clz, nativeMethods, sizeof(nativeMethods) / sizeof(nativeMethods[0]));

    return JNI_VERSION_1_4;
}
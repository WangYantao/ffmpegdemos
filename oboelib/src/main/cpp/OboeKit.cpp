//
// Created by 12418 on 2019/10/24.
//
#include <string>
#include <jni.h>
#include <android/input.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" {
}

jstring getOboeName(JNIEnv *env, jobject obj){
    return env->NewStringUTF("wangyt");
}

void touchEvent(JNIEnv *env, jobject obj, jint action){
    switch (action){
        case AMOTION_EVENT_ACTION_DOWN:
            audioEngine->setToneOn(true);
            break;
        case AMOTION_EVENT_ACTION_UP:
            audioEngine->setToneOn(false);
            break;
        default:
            break;
    }
}

void startEngine(JNIEnv *env, jobject obj){
    audioEngine->start();
}

void stopEngine(JNIEnv *env, jobject obj){
    audioEngine->stop();
}

//方法数组，正是这个，可以动态调用任意 native 方法
JNINativeMethod nativeMethods[] = {
        {"getOboeName", "()Ljava/lang/String;", (void *) getOboeName},
        {"touchEvent", "(I)V", (void *) touchEvent},
        {"startEngine", "()V", (void *) startEngine},
        {"stopEngine", "()V", (void *) stopEngine}
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
//
// Created by 12418 on 2019/10/24.
//
#include <string>
#include <jni.h>
#include <oboe/Oboe.h>

extern "C" {
}

jstring getOboeName(JNIEnv *env, jobject obj){

    return env->NewStringUTF("wangyt");
}

//方法数组，正是这个，可以动态调用任意 native 方法
JNINativeMethod nativeMethods[] = {
        {"getOboeName", "()Ljava/lang/String;", (void *) getOboeName}
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
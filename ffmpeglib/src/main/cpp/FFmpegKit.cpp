//
// Created by 12418 on 2019/10/24.
//
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/log.h>

extern "C" {

#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/imgutils.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#include "libx264/x264.h"
}

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "player", FORMAT, ##__VA_ARGS__);

jstring getFFmpegName(JNIEnv *env, jobject obj) {
    return env->NewStringUTF(avcodec_configuration());
}

void playVideo(JNIEnv *env, jobject instance, jstring path_, jobject surface){
    //媒体路径
    const char *path = env->GetStringUTFChars(path_, 0);
    //注册ffmpeg组件
    avformat_network_init();
    av_register_all();
    //初始化 AVFormatContext
    AVFormatContext *format_context = avformat_alloc_context();
    //打开媒体
    if (avformat_open_input(&format_context, path, NULL, NULL) < 0){
        LOGE("player error: file can not open");
        return;
    }
    //获取流信息
    if (avformat_find_stream_info(format_context, NULL) < 0){
        LOGE("player error: stream info find failed");
        return;
    }
    //查找第一个视频流
    int video_stream_index = -1;
    for(int i = 0; i < format_context->nb_streams; i++){
        if (format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && video_stream_index < 0){
            video_stream_index = i;
        }
    }
    if (video_stream_index == -1){
        LOGE("player error: can not find video stream");
        return;
    }
    //查找解码器
    AVCodec *video_codec = avcodec_find_decoder(format_context->streams[video_stream_index]->codecpar->codec_id);
    if (video_codec == NULL){
        LOGE("player error: can not find video codec");
        return;
    }
    //初始化 AVCodecContext
    AVCodecContext *video_codec_context = avcodec_alloc_context3(video_codec);
    avcodec_parameters_to_context(video_codec_context, format_context->streams[video_stream_index]->codecpar);
    //打开解码器
    if (avcodec_open2(video_codec_context, video_codec, NULL) < 0){
        LOGE("player error: can not open video decoder");
        return;
    }
    //创建native播放窗口
    ANativeWindow *native_window = ANativeWindow_fromSurface(env, surface);
    if (native_window == NULL){
        LOGE("player error: can not create native window");
        return;
    }
    //配置native窗口的buffer尺寸
    int video_width = video_codec_context->width;
    int video_height = video_codec_context->height;
    if (ANativeWindow_setBuffersGeometry(native_window, video_width, video_height, WINDOW_FORMAT_RGBA_8888) < 0){
        LOGE("player error: can not set native window buffer geometry");
        return;
    }
    //native 窗口buffer
    ANativeWindow_Buffer window_buffer;
    //packet(解封装后的数据包)、frame（解码后的数据帧）、rgba_frame（转换后用来显示的数据帧）
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    AVFrame *rgba_frame = av_frame_alloc();
    //配置输出buffer
    int buffer_size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, video_width, video_height, 1);
    uint8_t *out_buffer = (uint8_t *)av_malloc(buffer_size * sizeof(uint8_t));
    av_image_fill_arrays(rgba_frame->data, rgba_frame->linesize, out_buffer, AV_PIX_FMT_RGBA, video_width, video_height, 1);
    //数据格式转换
    struct SwsContext *data_convert_context = sws_getContext(video_width,video_height, video_codec_context->pix_fmt, video_width, video_height, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL,NULL,NULL);
    //读取数据流中的数据帧
    while (av_read_frame(format_context, packet) >= 0){
        //处理视频流
        if (packet->stream_index == video_stream_index){
            //向解码器发送 raw packet
            if (avcodec_send_packet(video_codec_context, packet) != 0){
                LOGE("player error: codec send packet error");
                return;
            }
            //从解码器接收解码后的视频帧
            //一个packet 可能对应多个 frame
            while (avcodec_receive_frame(video_codec_context, frame) == 0){
                //数据格式转换
                int result = -1;
                result = sws_scale(data_convert_context, (const uint8_t* const*) frame->data, frame->linesize, 0, video_height, rgba_frame->data, rgba_frame->linesize);
                if (result < 0){
                    LOGE("player error: data convert error");
                    return;
                }
                //播放
                result = ANativeWindow_lock(native_window, &window_buffer, NULL);
                if (result < 0){
                    LOGE("player error: can not lock native window");
                    return;
                } else{
                    // 将图像绘制到界面上
                    // 注意 : 这里 rgba_frame 一行的像素和 window_buffer 一行的像素长度可能不一致
                    // 需要转换好 否则可能花屏
                    uint8_t *bits = (uint8_t *) window_buffer.bits;
                    for (int h = 0; h < video_height; h++) {
                        memcpy(bits + h * window_buffer.stride * 4,
                               out_buffer + h * rgba_frame->linesize[0],
                               rgba_frame->linesize[0]);
                    }
                    ANativeWindow_unlockAndPost(native_window);
                }
            }
        }
        //释放packet引用
        av_packet_unref(packet);
    }
    //释放资源
    sws_freeContext(data_convert_context);
    av_free(out_buffer);
    av_frame_free(&rgba_frame);
    av_frame_free(&frame);
    av_packet_free(&packet);
    ANativeWindow_release(native_window);
    avcodec_close(video_codec_context);
    avformat_close_input(&format_context);
    env->ReleaseStringUTFChars(path_,path);
}

//方法数组，正是这个，可以动态调用任意 native 方法
JNINativeMethod nativeMethods[] = {
        {"getFFmpegName", "()Ljava/lang/String;",                        (void *) getFFmpegName},
        {"playVideo",     "(Ljava/lang/String;Landroid/view/Surface;)V", (void *) playVideo}
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
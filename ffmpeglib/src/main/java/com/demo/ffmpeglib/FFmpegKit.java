package com.demo.ffmpeglib;

/**
 * Created by wangyt on 2019/10/24
 */
public class FFmpegKit {

    static {
        System.loadLibrary("ffmpeg-kit");
        System.loadLibrary("avutil");
        System.loadLibrary("fdk-aac");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("avfilter");
    }

    public native String getFFmpegName();
}

package com.demo.oboelib;

/**
 * Created by wangyt on 2019/10/28
 */
public class OboeKit {
    static {
        System.loadLibrary("oboe-kit");
    }

    public native String getOboeName();

    public native void startEngine();
    public native void stopEngine();
    public native void setRecording(boolean isRecording);
    public native void setPlaying(boolean isPlaying);
    public native void setLooping(boolean isOn);
}

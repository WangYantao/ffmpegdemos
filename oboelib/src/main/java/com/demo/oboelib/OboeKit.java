package com.demo.oboelib;

/**
 * Created by wangyt on 2019/10/28
 */
public class OboeKit {
    static {
        System.loadLibrary("oboe-kit");
    }

    public native String getOboeName();
}

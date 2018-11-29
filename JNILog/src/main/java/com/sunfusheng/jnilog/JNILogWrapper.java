package com.sunfusheng.jnilog;

import android.util.Log;

/**
 * @author by sunfusheng on 2018/11/22
 */
public class JNILogWrapper {

    static {
        System.loadLibrary("JNILog");
    }

    public static native String stringFromJNI();

    public static native void convertConfigModel(byte[] inputBytes, double factor, byte[] outputBytes);

    public static ConfigModel convertConfigModelWrapper(ConfigModel inputConfig, double factor) {
        ConfigModel outputConfig = new ConfigModel();
        byte[] outputBytes = outputConfig.toBytes();
        convertConfigModel(inputConfig.toBytes(), factor, outputBytes);
        outputConfig.fromBytes(outputBytes);
        return outputConfig;
    }

}

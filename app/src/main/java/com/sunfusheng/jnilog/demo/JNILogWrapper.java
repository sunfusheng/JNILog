package com.sunfusheng.jnilog.demo;

/**
 * @author by sunfusheng on 2018/11/22
 */
public class JNILogWrapper {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();
}

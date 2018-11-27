package com.sunfusheng.jnilog;

/**
 * @author by sunfusheng on 2018/11/22
 */
public class JNILogWrapper {

    static {
        System.loadLibrary("JNILog");
    }

    public static native String stringFromJNI();
}

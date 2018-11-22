package com.sunfusheng.jnilog.demo;

import android.text.TextUtils;
import android.util.Log;

/**
 * @author by sunfusheng on 2018/11/22
 */
public class AndroidLog {

    private static boolean isDebug = true;

    public static void setDebug(boolean debug) {
        isDebug = debug;
    }

    private static void log(int priority, String tag, String msg) {
        if (!isDebug || TextUtils.isEmpty(tag) || TextUtils.isEmpty(msg)) {
            return;
        }

        switch (priority) {
            case Log.DEBUG:
                Log.d(tag, msg);
                break;
            case Log.INFO:
                Log.i(tag, msg);
                break;
            case Log.WARN:
                Log.w(tag, msg);
                break;
            case Log.ERROR:
                Log.e(tag, msg);
                break;
        }
    }

    public static void logD(String tag, String msg) {
        log(Log.DEBUG, tag, msg);
    }

    public static void logI(String tag, String msg) {
        log(Log.INFO, tag, msg);
    }

    public static void logW(String tag, String msg) {
        log(Log.WARN, tag, msg);
    }

    public static void logE(String tag, String msg) {
        log(Log.ERROR, tag, msg);
    }
}

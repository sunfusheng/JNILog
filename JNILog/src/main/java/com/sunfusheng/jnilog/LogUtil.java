package com.sunfusheng.jnilog;

import android.text.TextUtils;
import android.util.Log;

/**
 * @author by sunfusheng on 2018/11/22
 */
public class LogUtil {

    private static boolean isDebug = true;

    public static void setDebug(boolean debug) {
        isDebug = debug;
    }

    private static void Log(int priority, String tag, String msg) {
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

    public static void LogD(String tag, String msg) {
        Log(Log.DEBUG, tag, msg);
    }

    public static void LogI(String tag, String msg) {
        Log(Log.INFO, tag, msg);
    }

    public static void LogW(String tag, String msg) {
        Log(Log.WARN, tag, msg);
    }

    public static void LogE(String tag, String msg) {
        Log(Log.ERROR, tag, msg);
    }
}

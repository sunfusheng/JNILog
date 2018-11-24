/**
 * @author by sunfusheng on 2018/11/22
 */

#include <android/log.h>
#include "jni_log.h"

static const char *AndroidLogClassName = "com/sunfusheng/jnilog/demo/LogUtil";

void setDebug(JNIEnv *env, jboolean debug) {
    if (env == NULL) {
        return;
    }
    jclass clazz = env->FindClass(AndroidLogClassName);
    if (clazz == NULL) {
        return;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, "setDebug", "(Z)V");
    env->CallStaticVoidMethod(clazz, methodId, debug);
}

void Log(JNIEnv *env, const char *methodName, const char *tag, const char *msg) {
    if (env == NULL) {
        return;
    }
    jclass clazz = env->FindClass(AndroidLogClassName);
    if (clazz == NULL) {
        return;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, methodName,
                                                "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(clazz, methodId, env->NewStringUTF(tag), env->NewStringUTF(msg));
}

void LogD(JNIEnv *env, const char *tag, const char *msg) {
    Log(env, "LogD", tag, msg);
}

void LogI(JNIEnv *env, const char *tag, const char *msg) {
    Log(env, "LogI", tag, msg);
}

void LogW(JNIEnv *env, const char *tag, const char *msg) {
    Log(env, "LogW", tag, msg);
}

void LogE(JNIEnv *env, const char *tag, const char *msg) {
    Log(env, "LogE", tag, msg);
}
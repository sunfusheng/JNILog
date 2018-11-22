//
// Created by sunfusheng on 2018/11/22.
//

#include <android/log.h>
#include "jni_log.h"

static const char *AndroidLogClassName = "com/sunfusheng/jnilog/demo/AndroidLog";
//JavaVM *javaVM = NULL;
//
//JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
//    javaVM = vm;
//    return JNI_VERSION_1_6;
//}

JNIEnv *getJNIEnv() {
    JNIEnv *env = NULL;
    __android_log_print(ANDROID_LOG_DEBUG, "---> L", "111");
    if (javaVM == NULL || javaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "---> L", "222");
        return NULL;
    }
    __android_log_print(ANDROID_LOG_DEBUG, "---> L", "333");
    return env;
}

void L::setDebug(jboolean debug) {
    JNIEnv *env = getJNIEnv();
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

 void Log(const char *methodName, const char *tag, const char *msg) {
    JNIEnv *env = getJNIEnv();
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

 void L::LogD(const char *tag, const char *msg) {
    Log("LogD", tag, msg);
}

 void L::LogI(const char *tag, const char *msg) {
    Log("LogI", tag, msg);
}

 void L::LogW(const char *tag, const char *msg) {
    Log("LogW", tag, msg);
}

 void L::LogE(const char *tag, const char *msg) {
    Log("LogE", tag, msg);
}
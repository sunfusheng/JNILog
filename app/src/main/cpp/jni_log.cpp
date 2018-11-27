/**
 * @author by sunfusheng on 2018/11/22
 */

#include "jni_log.h"

static const char *LogUtilClassName = "com/sunfusheng/jnilog/demo/LogUtil";
JavaVM *javaVM = NULL;

void onLoad(JavaVM *vm) {
    javaVM = vm;

}

void onUnload(JavaVM *vm) {

}

JNIEnv *getJNIEnv() {
    JNIEnv *env = NULL;
    if (javaVM == NULL || javaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return NULL;
    }
    return env;
}

void setDebug(jboolean debug) {
    JNIEnv *env = getJNIEnv();
    if (env == NULL) {
        return;
    }
    jclass clazz = env->FindClass(LogUtilClassName);
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
    jclass clazz = env->FindClass(LogUtilClassName);
    if (clazz == NULL) {
        return;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, methodName,
                                                "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(clazz, methodId, env->NewStringUTF(tag), env->NewStringUTF(msg));
}

void LogD(const char *tag, const char *msg) {
    Log("LogD", tag, msg);
}

void LogI(const char *tag, const char *msg) {
    Log("LogI", tag, msg);
}

void LogW(const char *tag, const char *msg) {
    Log("LogW", tag, msg);
}

void LogE(const char *tag, const char *msg) {
    Log("LogE", tag, msg);
}
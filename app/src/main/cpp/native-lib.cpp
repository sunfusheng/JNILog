#include <jni.h>
#include <android/log.h>
#include "jni_log.h"

extern "C" {

static const char *TAG = "---> JNI";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/demo/JNILogWrapper";

jstring jniString(JNIEnv *env, jclass clazz) {
    LogD(env, TAG, "jniString() is Called");

    LogD(env, TAG, "test LogD()");
    LogI(env, TAG, "test LogI()");
    LogW(env, TAG, "test LogW()");
    LogE(env, TAG, "test LogE()");

    return env->NewStringUTF("jniString() is Called from C++");
}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) jniString}
};

static int jniRegisterNativeMethods(JNIEnv *env) {
    jclass clazz = env->FindClass(JNILogWrapperClassName);
    if (clazz == NULL) {
        return JNI_ERR;
    }

    int result = 0;
    int methods_count = sizeof(jni_methods_table) / sizeof(JNINativeMethod);
    if (env->RegisterNatives(clazz, jni_methods_table, methods_count) != JNI_OK) {
        result = JNI_ERR;
    }

    env->DeleteLocalRef(clazz);
    return result;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm == NULL || vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    if (env == NULL) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    LogD(env, TAG, "JNI_OnLoad() is called");
    return JNI_VERSION_1_6;
}

}


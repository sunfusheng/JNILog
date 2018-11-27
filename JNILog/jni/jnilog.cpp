#include "log.h"

extern "C" {

static const char *TAG = "---> JNI";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/JNILogWrapper";

jstring stringFromJNI(JNIEnv *env, jclass clazz) {
    LogD(TAG, "jniString() is Called");

    LogD(TAG, "test LogD()");
    LogI(TAG, "test LogI()");
    LogW(TAG, "test LogW()");
    LogE(TAG, "test LogE()");

    return env->NewStringUTF("stringFromJNI() is Called from C++");
}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) stringFromJNI}
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
    onLoad(vm);

    JNIEnv *env = getJNIEnv();
    if (env == NULL) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    LogD(TAG, "JNI_OnLoad() is called");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    onUnload(vm);
    LogD(TAG, "JNI_OnUnload() is called");
}

}


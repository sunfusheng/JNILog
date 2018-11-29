#include "log.h"

extern "C" {

static const char *TAG = "---> JNI";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/JNILogWrapper";

JNIEXPORT jstring JNICALL stringFromJNI(JNIEnv *env, jclass clazz) {
    LogD(TAG, "jniString() is Called");
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

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    onLoad(vm);
    LogD(TAG, "JNI_OnLoad() is called");

    JNIEnv *env = getJNIEnv();
    if (env == NULL) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    onUnload(vm);
    LogD(TAG, "JNI_OnUnload() is called");
}

}

#include <jni.h>
#include <android/log.h>
#include "jni_log.h"

extern "C" {

static const char *TAG = "---> JNI";
//static const char *AndroidLogClassName = "com/sunfusheng/jnilog/demo/AndroidLog";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/demo/JNILogWrapper";
//JavaVM *javaVM = NULL;

//void setDebug(jboolean debug);
//void LogD(const char *tag, const char *msg);
//void LogI(const char *tag, const char *msg);
//void LogW(const char *tag, const char *msg);
//void LogE(const char *tag, const char *msg);

JNIEnv *getJNIEnv() {
    JNIEnv *env = NULL;
    if (javaVM == NULL || javaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return NULL;
    }
    return env;
}

#define LTAG "---> LTAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LTAG, __VA_ARGS__)

jstring jniString(JNIEnv *env, jclass clazz) {
    L::LogD(TAG, "jniString() is Called");

    LOGD("1+1=%d", 2);

//    L::LogD(TAG, "test LogD()");
//    L::LogI(TAG, "test LogI()");
//    L::LogW(TAG, "test LogW()");
//    L::LogE(TAG, "test LogE()");

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
    javaVM = vm;
    L::LogD(TAG, "JNI_OnLoad() is called");

    JNIEnv *env = getJNIEnv();
    if (env == NULL) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    return JNI_VERSION_1_6;
}

//void setDebug(jboolean debug) {
//    JNIEnv *env = getJNIEnv();
//    if (env == NULL) {
//        return;
//    }
//    jclass clazz = env->FindClass(AndroidLogClassName);
//    if (clazz == NULL) {
//        return;
//    }
//    jmethodID methodId = env->GetStaticMethodID(clazz, "setDebug", "(Z)V");
//    env->CallStaticVoidMethod(clazz, methodId, debug);
//}
//
//void Log(const char *methodName, const char *tag, const char *msg) {
//    JNIEnv *env = getJNIEnv();
//    if (env == NULL) {
//        return;
//    }
//    jclass clazz = env->FindClass(AndroidLogClassName);
//    if (clazz == NULL) {
//        return;
//    }
//    jmethodID methodId = env->GetStaticMethodID(clazz, methodName,
//                                                "(Ljava/lang/String;Ljava/lang/String;)V");
//    env->CallStaticVoidMethod(clazz, methodId, env->NewStringUTF(tag), env->NewStringUTF(msg));
//}
//
//void LogD(const char *tag, const char *msg) {
//    Log("LogD", tag, msg);
//}
//
//void LogI(const char *tag, const char *msg) {
//    Log("LogI", tag, msg);
//}
//
//void LogW(const char *tag, const char *msg) {
//    Log("LogW", tag, msg);
//}
//
//void LogE(const char *tag, const char *msg) {
//    Log("LogE", tag, msg);
//}

}


#include <string.h>
#include <stdio.h>

#include "log.h"

extern "C" {

static const char *TAG = "---> JNI";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/JNILogWrapper";

typedef struct {
    int x;
    float y;
    double z;
} Config;

char *convertJByteArrayToChars(JNIEnv *env, jbyteArray byteArray) {
    jbyte *bytes = env->GetByteArrayElements(byteArray, 0);
    int byteArrayLength = env->GetArrayLength(byteArray);
    char *chars = new char[byteArrayLength + 1];
    memset(chars, 0, (size_t) (byteArrayLength + 1));
    memcpy(chars, bytes, (size_t) byteArrayLength);
    chars[byteArrayLength] = 0;
    env->ReleaseByteArrayElements(byteArray, bytes, 0);
    return chars;
}

JNIEXPORT jstring JNICALL stringFromJNI(JNIEnv *env, jclass clazz) {
    LogD(TAG, "jniString() is Called");
    return env->NewStringUTF("stringFromJNI() is Called from C++");
}

JNIEXPORT void JNICALL
convertConfig(JNIEnv *env, jclass clazz, jbyteArray inputBytes, jdouble factor,
              jbyteArray outputBytes) {
    LogD(TAG, "printConfigModel() is Called");

    char *data = convertJByteArrayToChars(env, inputBytes);
    Config config;
    memcpy(&config, data, sizeof(Config));

    char log[128];
    sprintf(log, "输入配置：int x=%d, float y=%f, double z=%lf", config.x, config.y, config.z);
    LogD(TAG, log);

    sprintf(log, "乘数因子：double factor=%lf", factor);
    LogD(TAG, log);

    config.x *= factor;
    config.y *= factor;
    config.z *= factor;

    sprintf(log, "输出配置：int x=%d, float y=%f, double z=%lf", config.x, config.y, config.z);
    LogD(TAG, log);

    jbyte *bytes = env->GetByteArrayElements(outputBytes, 0);
    memcpy(bytes, (char *) &config, sizeof(Config));
    env->ReleaseByteArrayElements(outputBytes, bytes, 0);
    delete data;
}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI",      "()Ljava/lang/String;", (void *) stringFromJNI},
        {"convertConfigModel", "([BD[B)V",             (void *) convertConfig},
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


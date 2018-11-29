#include <string.h>
#include "log.h"

extern "C" {

static const char *TAG = "---> JNI";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/JNILogWrapper";

typedef struct {
    int x;
    float y;
    double z;
} Config;

char *convertJByteArrayToCharPointer(JNIEnv *env, jbyteArray byteArray) {
    char *chars = NULL;
    jbyte *bytes;
    bytes = env->GetByteArrayElements(byteArray, 0);
    int chars_len = env->GetArrayLength(byteArray);
    chars = new char[chars_len + 1];
    memset(chars, 0, chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;
    env->ReleaseByteArrayElements(byteArray, bytes, 0);
    return chars;
}

JNIEXPORT jstring JNICALL stringFromJNI(JNIEnv *env, jclass clazz) {
    LogD(TAG, "jniString() is Called");
    return env->NewStringUTF("stringFromJNI() is Called from C++");
}

JNIEXPORT void JNICALL
convertConfigModel(JNIEnv *env, jclass clazz, jbyteArray inputBytes, jdouble factor,
                   jbyteArray outputBytes) {
    LogD(TAG, "printConfigModel() is Called");

    char *data = convertJByteArrayToCharPointer(env, inputBytes);
    Config config;
    memcpy(&config, data, sizeof(Config));
    __android_log_print(ANDROID_LOG_DEBUG, TAG,
                        "int x=%d, float y=%f, double z=%lf",
                        config.x, config.y, config.z);

    config.x *= factor;
    config.y *= factor;
    config.z *= factor;

    jbyte *bytes = env->GetByteArrayElements(outputBytes, 0);
    char *result = (char *) bytes;
    memcpy(result, (char *) &config, sizeof(Config));
    env->ReleaseByteArrayElements(outputBytes, bytes, 0);

//    char paraByteArrays[bytesCount];
//    memset(paraByteArrays, 0, bytesCount);
//    jbyte *rParaBody = env->GetByteArrayElements(byteArray, 0);
//    char *rParaData = (char *) rParaBody;
//    memcpy(paraByteArrays, rParaData, bytesCount);
//    env->ReleaseByteArrayElements(byteArray, rParaBody, 0);
//
//    memcpy(&config, &paraByteArrays, sizeof(Config));
//    __android_log_print(ANDROID_LOG_DEBUG, "---> ", "int x=%d, float y=%f, double z=%lf", config.x,
//                        config.y, config.z);
}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI",      "()Ljava/lang/String;", (void *) stringFromJNI},
        {"convertConfigModel", "([BD[B)V",             (void *) convertConfigModel},
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


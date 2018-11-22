#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {

jstring getStringFromJNI(JNIEnv *env, jclass clazz) {
    std::string hello = "Hello from C++, modified by sunfusheng.";
    return env->NewStringUTF(hello.c_str());
}

static const char *className = "com/sunfusheng/jnilog/demo/AndroidLog";

void setDebug(JNIEnv *env, jclass clazz, jboolean debug) {

}

void LOGD(JNIEnv *env, jclass clazz, std::string tag, std::string msg) {
}

void LOGI(JNIEnv *env, jclass clazz, std::string tag, std::string msg) {

}


JavaVM *javaVM;

void LOGW(const char *tag, const char *msg) {
    JNIEnv *env = NULL;
    if (javaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        return;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, "logW",
                                                "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(clazz, methodId, env->NewStringUTF(tag), env->NewStringUTF(msg));
    return;
}

void LOGE(JNIEnv *env, jclass clazz, std::string tag, std::string msg) {

}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) getStringFromJNI}
};

static int jniRegisterNativeMethods(JNIEnv *env) {
    jclass clazz = env->FindClass("com/sunfusheng/jnilog/demo/JNILogWrapper");
    if (clazz == NULL) {
        return JNI_ERR;
    }

    int result = 0;
    int methods_count = sizeof(jni_methods_table) / sizeof(JNINativeMethod);
    if (env->RegisterNatives(clazz, jni_methods_table, methods_count) < 0) {
        result = JNI_ERR;
    }

    env->DeleteLocalRef(clazz);
    return result;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_DEBUG, "---> JNI", "JNI_OnLoad() is called");

    javaVM = vm;
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    LOGW("---> JNI", "test java logW!!!");
    return JNI_VERSION_1_6;
}

}


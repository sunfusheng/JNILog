#include <jni.h>
#include <string>

extern "C" {

static const char *TAG = "---> JNI";
static const char *AndroidLogClassName = "com/sunfusheng/jnilog/demo/AndroidLog";
static const char *JNILogWrapperClassName = "com/sunfusheng/jnilog/demo/JNILogWrapper";
JavaVM *javaVM = NULL;

void setDebug(jboolean debug);
void LogD(const char *tag, const char *msg);
void LogI(const char *tag, const char *msg);
void LogW(const char *tag, const char *msg);
void LogE(const char *tag, const char *msg);

JNIEnv *getJNIEnv() {
    JNIEnv *env = NULL;
    if (javaVM == NULL || javaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return NULL;
    }
    return env;
}

jstring getStringFromJNI(JNIEnv *env, jclass clazz) {
    LogD(TAG, "getStringFromJNI() is Called");

    LogD(TAG, "test LogD()");
    LogI(TAG, "test LogI()");
    LogW(TAG, "test LogW()");
    LogE(TAG, "test LogE()");

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static JNINativeMethod jni_methods_table[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) getStringFromJNI}
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
    LogD(TAG, "JNI_OnLoad() is called");

    JNIEnv *env = getJNIEnv();
    if (env == NULL) {
        return JNI_ERR;
    }

    jniRegisterNativeMethods(env);

    return JNI_VERSION_1_6;
}


void setDebug(jboolean debug) {
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

}


//
// Created by sunfusheng on 2018/11/27.
//

#include "global.h"

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

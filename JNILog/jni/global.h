//
// Created by sunfusheng on 2018/11/27.
//

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <jni.h>

extern JavaVM *javaVM;

void onLoad(JavaVM *vm);

void onUnload(JavaVM *vm);

JNIEnv *getJNIEnv();

#endif

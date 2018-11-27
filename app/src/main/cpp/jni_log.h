/**
 * @author by sunfusheng on 2018/11/22
 */

#ifndef _JNI_LOG_H_
#define _JNI_LOG_H_

#include <jni.h>

extern JavaVM *javaVM;

void onLoad(JavaVM *vm);

void onUnload(JavaVM *vm);

void setDebug(jboolean debug);

void LogD(const char *tag, const char *msg);

void LogI(const char *tag, const char *msg);

void LogW(const char *tag, const char *msg);

void LogE(const char *tag, const char *msg);

#endif
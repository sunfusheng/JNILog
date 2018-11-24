/**
 * @author by sunfusheng on 2018/11/22
 */

#ifndef _JNI_LOG_H_
#define _JNI_LOG_H_

#include <jni.h>

void setDebug(JNIEnv *env, jboolean debug);

void LogD(JNIEnv *env, const char *tag, const char *msg);

void LogI(JNIEnv *env, const char *tag, const char *msg);

void LogW(JNIEnv *env, const char *tag, const char *msg);

void LogE(JNIEnv *env, const char *tag, const char *msg);

#endif
/**
 * @author by sunfusheng on 2018/11/22
 */

#ifndef _JNI_LOG_H_
#define _JNI_LOG_H_

#include "global.h"
#include <android/log.h>

void setDebug(jboolean debug);

void LogD(const char *tag, const char *msg);

void LogI(const char *tag, const char *msg);

void LogW(const char *tag, const char *msg);

void LogE(const char *tag, const char *msg);

#endif
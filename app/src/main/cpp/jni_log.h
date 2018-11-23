/**
 * @author by sunfusheng on 2018/11/22
 */

#ifndef JNILOG_JNI_LOG1_H
#define JNILOG_JNI_LOG1_H

#include <jni.h>

static JavaVM *javaVM = NULL;

class L {

public:
    static void setDebug(jboolean debug);

    static void LogD(const char *tag, const char *msg);

    static void LogI(const char *tag, const char *msg);

    static void LogW(const char *tag, const char *msg);

    static void LogE(const char *tag, const char *msg);
};

#endif //JNILOG_JNI_LOG1_H

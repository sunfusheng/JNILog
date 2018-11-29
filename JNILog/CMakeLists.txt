
cmake_minimum_required(VERSION 3.4.1)

set(SOURCE_SET
        jni/global.cpp
        jni/log.cpp
        jni/JNILog.cpp
        )

add_library(
        JNILog
        SHARED
        ${SOURCE_SET})

find_library(
        log-lib
        log)

target_link_libraries(
        JNILog
        ${log-lib})
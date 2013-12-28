#pragma once

#include <jni.h>
#include <android/log.h>

#define DEBUG 1

#define LOG_TAG "NativeActivity"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)

#else
#define LOGV(...)
#endif

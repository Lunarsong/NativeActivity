LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeActivity
LOCAL_SRC_FILES := NativeActivity.cpp Android.cpp
APP_STL := gnustl_shared
LOCAL_CFLAGS    := -Wall -fexceptions -frtti
LOCAL_CPPFLAGS  := -DNULL=0  -D_LIB=1

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := NativeActivityRuntimeUnstripped
LOCAL_SRC_FILES := AndroidMain.cpp
LOCAL_CFLAGS    := -Wall -fexceptions
LOCAL_CPPFLAGS  := -DNULL=0 -D_LIB=1
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2

LOCAL_WHOLE_STATIC_LIBRARIES := NativeActivity

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := NativeActivityRuntime
LOCAL_SRC_FILES := AndroidMain.cpp
LOCAL_CFLAGS    := -Wall -fexceptions
LOCAL_CPPFLAGS  := -DNULL=0 -D_LIB=1
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2

include $(BUILD_SHARED_LIBRARY)
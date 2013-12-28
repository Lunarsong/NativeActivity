#pragma once

#include <jni.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "AndroidMessage.h"

typedef void (*MessageCallbackFunction)( const AndroidMessage& );

class NativeActivity
{
public:
	static void PollEvents();
	static void SetEventCallback( MessageCallbackFunction pCallback );

	static void SetJNI( JNIEnv* pEnv, jobject pObj );

	static ANativeWindow* GetWindow();
	static bool IsVisible();

private:
	static bool PeekEvent( AndroidMessage& message );

	// Callbacks
	static MessageCallbackFunction s_mMessageCallback;

	// Member variables
	static ANativeWindow* 	s_pWindow;
	static bool				s_bIsVisible;

	// JNI Variables
	static JNIEnv* 	s_pEnv;
	static jobject 	s_pObj;
	static jclass	s_pJavaClass;

	static jmethodID	s_hPeekMessageMethod;
	static jmethodID	s_hPollMessagesMethod;

	// Message class
	static jclass	s_pMessageClass;
	static jfieldID	s_hMessageIDField;
	static jfieldID s_hSurfaceField;
};

#ifndef _LIB
extern "C"
{
	void init_native_activity( JNIEnv* pEnv, jobject pObj )
	{
		NativeActivity::SetJNI( pEnv, pObj );
	}
}
#endif

#pragma once

#include "NativeActivity.h"

class Android
{
public:
	static void PollEvents();
	static void SetEventCallback( MessageCallbackFunction pCallback );

	static void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );

	static ANativeWindow* GetWindow();
	static bool IsWindowVisible();

	static void ShowKeyboard();
	static void HideKeyboard();

private:
	static NativeActivity s_NativeActivity;
};

#ifndef _LIB
extern "C"
{
	void init_native_activity( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface )
	{
		Android::SetJNI( pEnv, pObj, pInterface );
	}
}
#endif

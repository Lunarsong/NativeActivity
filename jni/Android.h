#pragma once

#include "NativeActivity.h"
#include "IAndroidHandler.h"
#include "AssetManager.h"

namespace Android
{
	void PollEvents();
	void SetEventCallback( MessageCallbackFunction pCallback );
	void SetEventHandler( IAndroidHandler* pHandler );

	void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );

	ANativeWindow* GetWindow();
	bool IsWindowVisible();

	void ShowKeyboard();
	void HideKeyboard();

	AssetManager& GetAssetManager();
};

#ifndef _LIB
extern "C"
{
	void init_native_activity( JNIEnv* pEnv, jobject pObj, Android::INativeInterface** pInterface );
}

#endif

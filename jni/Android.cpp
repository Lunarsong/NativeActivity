#include "Android.h"
#include "AndroidLog.h"

namespace Android
{
	NativeActivity s_NativeActivity = NativeActivity();
	static JNIEnv* s_pEnv = NULL;
	static jobject s_pActivity = NULL;

	NativeActivity& GetNativeActivity()
	{
		return s_NativeActivity;
	}

	JNIEnv* GetJNIEnv()
	{
		return s_pEnv;
	}

	jobject GetJNIActivity()
	{
		return s_pActivity;
	}

	void PollEvents()
	{
		s_NativeActivity.PollEvents();
	}

	void SetEventCallback( MessageCallbackFunction pCallback )
	{
		s_NativeActivity.SetEventCallback( pCallback );
	}

	void SetEventHandler( IAndroidHandler* pHandler )
	{
		s_NativeActivity.SetEventHandler( pHandler );
	}

	void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface )
	{
		LOGV( "[Android]: Setting JNI Environment." );
		s_pEnv = pEnv;

		s_NativeActivity.SetJNI( pEnv, pObj, pInterface );
		s_pActivity = s_NativeActivity.GetContext();
	}

	ANativeWindow* GetWindow()
	{
		return s_NativeActivity.GetWindow();
	}

	bool IsWindowVisible()
	{
		return s_NativeActivity.IsVisible();
	}

	void ShowKeyboard()
	{
		s_NativeActivity.ShowKeyboard();
	}

	void HideKeyboard()
	{
		s_NativeActivity.HideKeyboard();
	}

	AssetManager& GetAssetManager()
	{
		return s_NativeActivity.GetAssetManager();
	}

	const char* GetAppDir()
	{
		return s_NativeActivity.GetAppDir();
	}

	ClassLoader& GetClassLoader()
	{
		return s_NativeActivity.GetClassLoader();
	}

	NotificationManager& GetNotificationManager()
	{
		return s_NativeActivity.GetNotificationManager();
	}
}

extern "C"
{
	void init_native_activity( JNIEnv* pEnv, jobject pObj, Android::INativeInterface** pInterface )
	{
		Android::SetJNI( pEnv, pObj, pInterface );
	}
}

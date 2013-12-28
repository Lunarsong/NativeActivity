#pragma once

#include <jni.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "AndroidMessage.h"
#include "INativeInterface.h"

typedef void (*MessageCallbackFunction)( const AndroidMessage& );

class NativeActivity
{
public:
	static void PollEvents();
	static void SetEventCallback( MessageCallbackFunction pCallback );

	static void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );

	static ANativeWindow* GetWindow();
	static bool IsVisible();

	static void ShowKeyboard();
	static void HideKeyboard();

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

	static jmethodID	s_hShowKeyboardMethod;
	static jmethodID	s_hHideKeyboardMethod;

	// Message class
	static jclass	s_pMessageClass;
	static jfieldID	s_hMessageIDField;
	static jfieldID s_hSurfaceField;

	class NativeInterface : public INativeInterface
	{
	public:
		NativeInterface();
		~NativeInterface();

		virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight );

		virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
		virtual void OnKeyUp( int iKeyCode, int iUnicodeChar );
	};

	friend class NativeInterface;
};

#ifndef _LIB
extern "C"
{
	void init_native_activity( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface )
	{
		NativeActivity::SetJNI( pEnv, pObj, pInterface );
	}
}
#endif

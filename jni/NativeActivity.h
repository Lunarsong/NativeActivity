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
	void PollEvents();
	void SetEventCallback( MessageCallbackFunction pCallback );

	void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );

	ANativeWindow* GetWindow();
	bool IsVisible();

	void ShowKeyboard();
	void HideKeyboard();

private:
	NativeActivity();
	~NativeActivity();

	bool PeekEvent( AndroidMessage& message );

	// Callbacks
	MessageCallbackFunction m_pMessageCallback;

	// Member variables
	ANativeWindow* 	m_pWindow;
	bool			m_bIsVisible;

	// JNI Variables
	JNIEnv* 	m_pEnv;
	jobject 	m_pObj;
	jclass		m_pJavaClass;

	jmethodID	m_hPeekMessageMethod;	// Peek message
	jmethodID	m_hPollMessagesMethod;	// Poll messages

	jmethodID	m_hShowKeyboardMethod; // Show keyboard
	jmethodID	m_hHideKeyboardMethod; // Hide keyboard

	// Message class
	jclass		m_hMessageClass;
	jfieldID	m_hMessageIDField;
	jfieldID 	m_hSurfaceField;

	class NativeInterface : public INativeInterface
	{
	public:
		NativeInterface( NativeActivity* pActivity );
		~NativeInterface();

		virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight );

		virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
		virtual void OnKeyUp( int iKeyCode, int iUnicodeChar );

	private:
		NativeActivity* m_pActivity;
	};

	friend class NativeInterface;
	friend class Android;
};

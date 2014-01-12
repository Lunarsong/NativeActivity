#pragma once

#include <jni.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "AndroidMessage.h"
#include "INativeInterface.h"
#include "AssetManager.h"
#include "IAndroidHandler.h"

namespace Android
{
	typedef void (*MessageCallbackFunction)( const AndroidMessage& );

	class NativeActivity
	{
	public:
		void PollEvents();
		void SetEventCallback( MessageCallbackFunction pCallback );
		void SetEventHandler( IAndroidHandler* pHandler );

		void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );

		ANativeWindow* GetWindow();
		bool IsVisible() const;

		void ShowKeyboard();
		void HideKeyboard();

		NativeActivity();
		~NativeActivity();

		AssetManager& GetAssetManager();
		const char* GetAppDir() const;

		JNIEnv* GetJNI();
		jobject	GetObject();
		jclass 	GetClass();

	private:
		AssetManager m_AssetManager;

		bool PeekEvent( AndroidMessage& message );
		void DispatchMessage( const AndroidMessage& message );
		void DispatchMessage( AndroidMessageType eMessage );

		void SetSurface( jobject pSurface );
		void SetVisible( bool bVisible );

		// Callbacks
		MessageCallbackFunction m_pMessageCallback;
		IAndroidHandler*		m_pEventHandler;

		// Member variables
		char*			m_pAppDir;
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

		jmethodID	m_hGetAppDirMethod;

		// Context
		jmethodID	m_hGetContextMethod;
		jobject		m_pContext;

		// Message class
		jclass		m_hMessageClass;
		jfieldID	m_hMessageIDField;

		class NativeInterface : public INativeInterface
		{
		public:
			NativeInterface( NativeActivity* pActivity );
			~NativeInterface();

			// Application state
			virtual void OnApplicationShutdown();
			virtual void OnApplicationPaused();
			virtual void OnApplicationResumed();
			virtual void OnLowMemory();

			// Surface
			virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight );
			virtual void OnSurfaceCreated( jobject pSurface );
			virtual void OnSurfaceDestroyed();

			// Window state
			virtual void OnWindowHidden();
			virtual void OnWindowShown();

			// Input
			virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
			virtual void OnKeyUp( int iKeyCode, int iUnicodeChar );


		private:
			NativeActivity* m_pActivity;
		};

		friend class NativeInterface;
		friend void SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface );
		void InitAppDir();
	};

}

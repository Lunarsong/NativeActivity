#include "NativeActivity.h"
#include "AndroidLog.h"

#include <assert.h>

namespace Android
{
	NativeActivity::NativeActivity()
	: m_AssetManager( this )
	{
		// Call-backs
		m_pEventHandler = NULL;
		m_pMessageCallback = NULL;

		// Member variables
		m_pWindow = NULL;
		m_bIsVisible = false;

		// JNI Environment
		m_pEnv = NULL;

		// NativeActivity class and reference
		m_pObj = NULL;
		m_pJavaClass = NULL;

		// NativeActivity's methods
		m_hPeekMessageMethod = NULL;
		m_hPollMessagesMethod = NULL;

		m_hShowKeyboardMethod = NULL;
		m_hHideKeyboardMethod = NULL;

		// Message class
		m_hMessageClass = NULL;

		// Message methods
		m_hMessageIDField = NULL;
	}

	NativeActivity::~NativeActivity()
	{
		m_pEnv->DeleteGlobalRef( m_pObj );
	}

	JNIEnv* NativeActivity::GetJNI()
	{
		return m_pEnv;
	}

	jobject	NativeActivity::GetObject()
	{
		return m_pObj;
	}

	jclass NativeActivity::GetClass()
	{
		return m_pJavaClass;
	}

	void NativeActivity::PollEvents()
	{
		// Call Java's poll method
		m_pEnv->CallVoidMethod( m_pObj, m_hPollMessagesMethod );

		AndroidMessage message;
		while ( PeekEvent( message ) )
		{
			// Send the message to callback
			DispatchMessage( message );
		}
	}

	void NativeActivity::SetEventCallback( MessageCallbackFunction pCallback )
	{
		m_pMessageCallback = pCallback;
	}

	void NativeActivity::SetEventHandler( IAndroidHandler* pHandler )
	{
		m_pEventHandler = pHandler;
	}

	bool NativeActivity::PeekEvent( AndroidMessage& message )
	{
		jobject pObject = m_pEnv->CallObjectMethod( m_pObj, m_hPeekMessageMethod );
		if ( pObject )
		{
			message.iMessageID = m_pEnv->GetIntField( pObject, m_hMessageIDField );

			return true;
		}

		return false;
	}

	void NativeActivity::DispatchMessage( const AndroidMessage& message )
	{
		if ( m_pMessageCallback != NULL )
		{
			// Send message
			m_pMessageCallback( message );
		}
	}

	void NativeActivity::DispatchMessage( AndroidMessageType eMessage )
	{
		if ( m_pMessageCallback != NULL )
		{
			AndroidMessage message;
			message.iMessageID = eMessage;

			// Send message
			m_pMessageCallback( message );
		}
	}

	void NativeActivity::SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface )
	{
		m_pEnv = pEnv;
		m_pObj = pEnv->NewGlobalRef( pObj );

		m_pJavaClass = pEnv->GetObjectClass( pObj );

		// Retrieve Java methods
		m_hPeekMessageMethod = pEnv->GetMethodID( m_pJavaClass, "peekMessage", "()Lcom/lunarsong/android/NativeMessage;" );
		m_hPollMessagesMethod = pEnv->GetMethodID( m_pJavaClass, "pollMessages", "()V" );

		m_hShowKeyboardMethod = pEnv->GetMethodID( m_pJavaClass, "showKeyboard", "()V" );
		m_hHideKeyboardMethod = pEnv->GetMethodID( m_pJavaClass, "hideKeyboard", "()V" );

		// Message class
		m_hMessageClass 	= pEnv->FindClass( "com/lunarsong/android/NativeMessage" );
		m_hMessageIDField 	= pEnv->GetFieldID( m_hMessageClass, "mID", "I" );

		// Init the Asset Manager
		m_AssetManager.Init();

		*pInterface = new NativeInterface( this );
	}

	void NativeActivity::SetSurface( jobject pSurface )
	{
		if ( pSurface )
		{
			m_pWindow = ANativeWindow_fromSurface( m_pEnv, pSurface );

			if ( m_pEventHandler )
			{
				m_pEventHandler->OnSurfaceCreated();
			}

			DispatchMessage( AndroidMessage_SurfaceCreated );
		}

		else
		{
			if ( m_pWindow )
			{
				ANativeWindow_release( m_pWindow );
				m_pWindow = NULL;

				if ( m_pEventHandler )
				{
					m_pEventHandler->OnSurfaceDestroyed();
				}

				DispatchMessage( AndroidMessage_SurfaceDestroyed );
			}
		}
	}

	ANativeWindow* NativeActivity::GetWindow()
	{
		return m_pWindow;
	}

	bool NativeActivity::IsVisible() const
	{
		return m_bIsVisible;
	}

	void NativeActivity::SetVisible( bool bVisible )
	{
		m_bIsVisible = bVisible;
	}

	void NativeActivity::ShowKeyboard()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hShowKeyboardMethod );
	}

	void NativeActivity::HideKeyboard()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hHideKeyboardMethod );
	}

	/**********************************************************************************/
	/*                                 NativeInterface                                */
	/**********************************************************************************/
	NativeActivity::NativeInterface::NativeInterface( NativeActivity* pActivity )
	{
		m_pActivity = pActivity;
	}

	NativeActivity::NativeInterface::~NativeInterface()
	{

	}

	void NativeActivity::NativeInterface::OnSurfaceCreated( jobject pSurface )
	{
		m_pActivity->SetSurface( pSurface );
	}

	void NativeActivity::NativeInterface::OnSurfaceChanged( int iFormat, int iWidth, int iHeight )
	{
		//LOGV( "[Native] OnSurfaceChanged: Width: %i, Height: %i, Format: %i.", iWidth, iHeight, iFormat );

		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnSurfaceChanged( iFormat, iWidth, iHeight );
		}

		// Create surface data
		AndroidSurfaceChanged surfaceChanged;
		surfaceChanged.iFormat 	= iFormat;
		surfaceChanged.iWidth	= iWidth;
		surfaceChanged.iHeight	= iHeight;

		// Create message
		AndroidMessage message;
		message.iMessageID = AndroidMessage_SurfaceChanged;
		message.pData = &surfaceChanged;

		// Send message
		m_pActivity->DispatchMessage( message );
	}

	void NativeActivity::NativeInterface::OnSurfaceDestroyed()
	{
		m_pActivity->SetSurface( NULL );
	}

	void NativeActivity::NativeInterface::OnApplicationPaused()
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnPause();
		}

		m_pActivity->DispatchMessage( AndroidMessage_ApplicationPaused );
	}

	void NativeActivity::NativeInterface::OnApplicationShutdown()
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnShutdown();
		}

		m_pActivity->DispatchMessage( AndroidMessage_ApplicationShutdown );
	}

	void NativeActivity::NativeInterface::OnLowMemory()
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnLowMemory();
		}

		m_pActivity->DispatchMessage( AndroidMessage_LowMemory );
	}

	void NativeActivity::NativeInterface::OnApplicationResumed()
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnResume();
		}

		m_pActivity->DispatchMessage( AndroidMessage_ApplicationResumed );
	}

	void NativeActivity::NativeInterface::OnWindowHidden()
	{
		m_pActivity->SetVisible( false );

		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnHidden();
		}

		m_pActivity->DispatchMessage( AndroidMessage_WindowHidden );
	}

	void NativeActivity::NativeInterface::OnWindowShown()
	{
		m_pActivity->SetVisible( true );

		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnVisible();
		}

		m_pActivity->DispatchMessage( AndroidMessage_WindowVisible );
	}

	void NativeActivity::NativeInterface::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnTouch( iPointerID, fPosX, fPosY, iAction );
		}

		// Create touch data
		AndroidTouch touch;
		touch.iPointerID = iPointerID;
		touch.fPosX = fPosX;
		touch.fPosY	= fPosY;
		touch.iAction = iAction;

		// Create message
		AndroidMessage message;
		message.iMessageID = AndroidMessage_OnTouch;
		message.pData = &touch;

		// Send message
		m_pActivity->DispatchMessage( message );
	}

	void NativeActivity::NativeInterface::OnKeyUp( int iKeyCode, int iUnicodeChar )
	{
		if ( m_pActivity->m_pEventHandler )
		{
			m_pActivity->m_pEventHandler->OnKey( iKeyCode, iUnicodeChar );
		}

		// Create key data
		AndroidKey keyMessage;
		keyMessage.iKeyCode = iKeyCode;
		keyMessage.iUnicodeChar = (wchar_t)iUnicodeChar;

		// Create message
		AndroidMessage message;
		message.iMessageID = AndroidMessage_OnKey;
		message.pData = &keyMessage;

		// Send message
		m_pActivity->DispatchMessage( message );
	}

	AssetManager& NativeActivity::GetAssetManager()
	{
		return m_AssetManager;
	}
}

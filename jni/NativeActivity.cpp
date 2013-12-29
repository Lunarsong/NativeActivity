#include "NativeActivity.h"
#include "AndroidLog.h"

#include <assert.h>

NativeActivity::NativeActivity()
{
	// PollEvents callback
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

}

void NativeActivity::PollEvents()
{
	assert( m_pCallback && "Must set a call message callback!" );

	// Call Java's poll method
	m_pEnv->CallVoidMethod( m_pObj, m_hPollMessagesMethod );

	AndroidMessage message;
	while ( PeekEvent( message ) )
	{
		m_pMessageCallback( message );
	}
}

void NativeActivity::SetEventCallback( MessageCallbackFunction pCallback )
{
	m_pMessageCallback = pCallback;
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
	m_pObj = pObj;

	m_pJavaClass = pEnv->GetObjectClass( pObj );

	// Retrieve Java methods
	m_hPeekMessageMethod = pEnv->GetMethodID( m_pJavaClass, "peekMessage", "()Lcom/lunarsong/android/NativeMessage;" );
	m_hPollMessagesMethod = pEnv->GetMethodID( m_pJavaClass, "pollMessages", "()V" );

	m_hShowKeyboardMethod = pEnv->GetMethodID( m_pJavaClass, "showKeyboard", "()V" );
	m_hHideKeyboardMethod = pEnv->GetMethodID( m_pJavaClass, "hideKeyboard", "()V" );

	// Message class
	m_hMessageClass 	= pEnv->FindClass( "com/lunarsong/android/NativeMessage" );
	m_hMessageIDField 	= pEnv->GetFieldID( m_hMessageClass, "mID", "I" );

	*pInterface = new NativeInterface( this );
}

void NativeActivity::SetSurface( jobject pSurface )
{
	if ( pSurface )
	{
		m_pWindow = ANativeWindow_fromSurface( m_pEnv, pSurface );

		DispatchMessage( AndroidMessage_SurfaceCreated );
	}

	else
	{
		if ( m_pWindow )
		{
			ANativeWindow_release( m_pWindow );
			m_pWindow = NULL;

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
	LOGV( "[Native] OnSurfaceChanged: Width: %i, Height: %i, Format: %i.", iWidth, iHeight, iFormat );

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
	m_pActivity->DispatchMessage( AndroidMessage_ApplicationPaused );
}

void NativeActivity::NativeInterface::OnApplicationResumed()
{
	m_pActivity->DispatchMessage( AndroidMessage_ApplicationResumed );
}

void NativeActivity::NativeInterface::OnWindowHidden()
{
	m_pActivity->SetVisible( false );

	m_pActivity->DispatchMessage( AndroidMessage_WindowHidden );
}

void NativeActivity::NativeInterface::OnWindowShown()
{
	m_pActivity->SetVisible( true );

	m_pActivity->DispatchMessage( AndroidMessage_WindowVisible );
}

void NativeActivity::NativeInterface::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
{
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

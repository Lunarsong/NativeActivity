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
	m_hSurfaceField = NULL;
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

		switch ( message.iMessageID )
		{
			case AndroidMessage_SurfaceCreated:
			{
				jobject pSurface = m_pEnv->GetObjectField( pObject, m_hSurfaceField );
				m_pWindow = ANativeWindow_fromSurface( m_pEnv, pSurface );
			} break;

			case AndroidMessage_SurfaceDestroyed:
			{
				ANativeWindow_release( m_pWindow );
				m_pWindow = NULL;
			} break;

			case AndroidMessage_WindowHidden:
			{
				m_bIsVisible = false;
			} break;

			case AndroidMessage_WindowVisible:
			{
				m_bIsVisible = true;
			} break;

			default:
				break;
		}

		return true;
	}

	return false;
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
	m_hSurfaceField 	= pEnv->GetFieldID( m_hMessageClass, "mSurface", "Landroid/view/Surface;" );

	*pInterface = new NativeInterface( this );
}

ANativeWindow* NativeActivity::GetWindow()
{
	return m_pWindow;
}

bool NativeActivity::IsVisible()
{
	return m_bIsVisible;
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

void NativeActivity::NativeInterface::OnSurfaceChanged( int iFormat, int iWidth, int iHeight )
{
	LOGV( "[Native] OnSurfaceChanged: Width: %i, Height: %i, Format: %i.", iWidth, iHeight, iFormat );

	if ( m_pActivity->m_pMessageCallback != NULL )
	{
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
		m_pActivity->m_pMessageCallback( message );
	}
}

void NativeActivity::NativeInterface::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
{
	if ( m_pActivity->m_pMessageCallback != NULL )
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
		m_pActivity->m_pMessageCallback( message );
	}
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
	m_pActivity->m_pMessageCallback( message );
}

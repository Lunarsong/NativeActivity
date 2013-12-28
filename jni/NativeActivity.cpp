#include "NativeActivity.h"
#include "AndroidLog.h"

#include <assert.h>

// PollEvents callback
MessageCallbackFunction NativeActivity::s_mMessageCallback = NULL;

// Member variables
ANativeWindow* NativeActivity::s_pWindow = NULL;
bool NativeActivity::s_bIsVisible = false;

// JNI Environment
JNIEnv* NativeActivity::s_pEnv = NULL;

// NativeActivity class and reference
jobject NativeActivity::s_pObj = NULL;
jclass NativeActivity::s_pJavaClass = NULL;

// NativeActivity's methods
jmethodID	NativeActivity::s_hPeekMessageMethod = NULL;
jmethodID	NativeActivity::s_hPollMessagesMethod = NULL;

jmethodID	NativeActivity::s_hShowKeyboardMethod = NULL;
jmethodID	NativeActivity::s_hHideKeyboardMethod = NULL;

// Message class
jclass NativeActivity::s_pMessageClass = NULL;

// Message methods
jfieldID NativeActivity::s_hMessageIDField = NULL;
jfieldID NativeActivity::s_hSurfaceField = NULL;


void NativeActivity::PollEvents()
{
	assert( s_pCallback && "Must set a call message callback!" );

	// Call Java's poll method
	s_pEnv->CallVoidMethod( s_pObj, s_hPollMessagesMethod );

	AndroidMessage message;
	while ( PeekEvent( message ) )
	{
		s_mMessageCallback( message );
	}
}

void NativeActivity::SetEventCallback( MessageCallbackFunction pCallback )
{
	s_mMessageCallback = pCallback;
}

bool NativeActivity::PeekEvent( AndroidMessage& message )
{
	jobject pObject = s_pEnv->CallObjectMethod( s_pObj, s_hPeekMessageMethod );
	if ( pObject )
	{
		message.iMessageID = s_pEnv->GetIntField( pObject, s_hMessageIDField );

		switch ( message.iMessageID )
		{
			case AndroidMessage_SurfaceCreated:
			{
				jobject pSurface = s_pEnv->GetObjectField( pObject, s_hSurfaceField );
				s_pWindow = ANativeWindow_fromSurface( s_pEnv, pSurface );
			} break;

			case AndroidMessage_SurfaceDestroyed:
			{
				ANativeWindow_release( s_pWindow );
				s_pWindow = NULL;
			} break;

			case AndroidMessage_WindowHidden:
			{
				s_bIsVisible = false;
			} break;

			case AndroidMessage_WindowVisible:
			{
				s_bIsVisible = true;
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
	s_pEnv = pEnv;
	s_pObj = pObj;

	s_pJavaClass = pEnv->GetObjectClass( pObj );

	// Retrieve Java methods
	s_hPeekMessageMethod = pEnv->GetMethodID( s_pJavaClass, "peekMessage", "()Lcom/lunarsong/android/NativeMessage;" );
	s_hPollMessagesMethod = pEnv->GetMethodID( s_pJavaClass, "pollMessages", "()V" );

	s_hShowKeyboardMethod = pEnv->GetMethodID( s_pJavaClass, "showKeyboard", "()V" );
	s_hHideKeyboardMethod = pEnv->GetMethodID( s_pJavaClass, "hideKeyboard", "()V" );

	// Message class
	s_pMessageClass 	= pEnv->FindClass( "com/lunarsong/android/NativeMessage" );
	s_hMessageIDField 	= pEnv->GetFieldID( s_pMessageClass, "mID", "I" );
	s_hSurfaceField 	= pEnv->GetFieldID( s_pMessageClass, "mSurface", "Landroid/view/Surface;" );

	*pInterface = new NativeInterface();
}

ANativeWindow* NativeActivity::GetWindow()
{
	return s_pWindow;
}

bool NativeActivity::IsVisible()
{
	return s_bIsVisible;
}

void NativeActivity::ShowKeyboard()
{
	s_pEnv->CallVoidMethod( s_pObj, s_hShowKeyboardMethod );
}

void NativeActivity::HideKeyboard()
{
	s_pEnv->CallVoidMethod( s_pObj, s_hHideKeyboardMethod );
}

/**********************************************************************************/
/*                                 NativeInterface                                */
/**********************************************************************************/
NativeActivity::NativeInterface::NativeInterface()
{

}

NativeActivity::NativeInterface::~NativeInterface()
{

}

void NativeActivity::NativeInterface::OnSurfaceChanged( int iFormat, int iWidth, int iHeight )
{
	LOGV( "[Native] OnSurfaceChanged: Width: %i, Height: %i, Format: %i.", iWidth, iHeight, iFormat );

	if ( s_mMessageCallback != NULL )
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
		s_mMessageCallback( message );
	}
}

void NativeActivity::NativeInterface::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
{
	if ( s_mMessageCallback != NULL )
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
		s_mMessageCallback( message );
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
	s_mMessageCallback( message );
}

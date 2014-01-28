/*
 * GooglePlayServices.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#include "GooglePlayServices.h"
#include "GoogleGames.h"
#include "GooglePlus.h"
#include "AndroidLog.h"
#include <cstring>

namespace Android
{
	jmethodID GooglePlayServices::m_hGetGamesClientMethod 			= NULL;
	jmethodID GooglePlayServices::m_hGetAppStateClientMethod 		= NULL;
	jmethodID GooglePlayServices::m_hGetPlusClientMethod 			= NULL;

	jmethodID GooglePlayServices::m_hIsSignedInMethod 				= NULL;	// bool isSignedIn()
	jmethodID GooglePlayServices::m_hBeginUserInitiatedSignInMethod = NULL;	// void beginUserInitiatedSignIn()
	jmethodID GooglePlayServices::m_hSignOutMethod 					= NULL;	// void signOut();
	jmethodID GooglePlayServices::m_hShowAlertMethod 				= NULL;	// void showAlert( String message )
	jmethodID GooglePlayServices::m_hShowAlertWithTitleMethod 		= NULL; // void showAlert( String title, String message )
	jmethodID GooglePlayServices::m_hEnableDebugLogMethod 			= NULL;	// void enableDebugLog( boolean enable, String tag )
	jmethodID GooglePlayServices::m_hGetInvitationIDMethod 			= NULL;	// String getInvitationId()
	jmethodID GooglePlayServices::m_hReconnectClientsMethod 		= NULL; // void reconnectClients( int iWhichClients );
	jmethodID GooglePlayServices::m_hGetScopesMethod 				= NULL;	// String getScopes()
	jmethodID GooglePlayServices::m_hGetScopesArrayMethod 			= NULL;	// String[] getScopesArray()
	jmethodID GooglePlayServices::m_hHasSignInErrorMethod 			= NULL;	// bool hasSignInError()
	jmethodID GooglePlayServices::m_hGetSignInErrorMethod 			= NULL;	// GameHelper.SignInFailureReason getSignInError()

	JNIEnv* GooglePlayServices::m_pEnv 		= NULL;
	jobject GooglePlayServices::m_pObj 		= NULL;
	jclass	GooglePlayServices::m_jClass	= NULL;

	char*	GooglePlayServices::m_pAccountName = NULL;

	ISignInListener* GooglePlayServices::s_pSignInListener = NULL;

	void GooglePlayServices::Init( JNIEnv* pEnv, jobject pObj )
	{
		LOGV( "Initialising GooglePlayServices" );
		m_pEnv = pEnv;
		m_pObj = pObj;

		m_jClass = m_pEnv->FindClass( "com/lunarsong/android/BaseGameActivity" );

		m_hBeginUserInitiatedSignInMethod 	= m_pEnv->GetMethodID( m_jClass, "beginUserInitiatedSignIn", "()V" );
		m_hSignOutMethod					= m_pEnv->GetMethodID( m_jClass, "signOut", "()V" );
		m_hIsSignedInMethod 				= m_pEnv->GetMethodID( m_jClass, "isSignedIn", "()Z" );

		m_hShowAlertMethod	 				= m_pEnv->GetMethodID( m_jClass, "showAlert", "(Ljava/lang/String;)V" );
		m_hShowAlertWithTitleMethod			= m_pEnv->GetMethodID( m_jClass, "showAlert", "(Ljava/lang/String;Ljava/lang/String;)V" );

		m_hHasSignInErrorMethod 			= m_pEnv->GetMethodID( m_jClass, "hasSignInError", "()Z" );

		GoogleGames::Init( pEnv, pObj, m_jClass );
		GooglePlus::Init( pEnv, pObj, m_jClass );
	}

	void GooglePlayServices::Shutdown()
	{
		if ( m_pAccountName )
		{
			delete [] m_pAccountName;
			m_pAccountName = NULL;
		}
	}

	/*const char* GooglePlayServices::GetAccountName()
	{
		return m_pAccountName;
	}*/

	void GooglePlayServices::OnSignInSucceeded( char* pAccountName  )
	{
		if ( m_pAccountName )
		{
			delete [] m_pAccountName;
			m_pAccountName = NULL;
		}

		m_pAccountName = pAccountName;

		if ( s_pSignInListener )
		{
			s_pSignInListener->OnSignInSucceeded();
		}
	}

	void GooglePlayServices::OnSignInFailed()
	{
		if ( s_pSignInListener )
		{
			s_pSignInListener->OnSignInFailed();
		}
	}

	void GooglePlayServices::SetSignInListener( ISignInListener* pListener )
	{
		s_pSignInListener = pListener;
	}

	void GooglePlayServices::SignIn()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hBeginUserInitiatedSignInMethod );
	}

	void GooglePlayServices::SignOut()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hSignOutMethod );
	}

	bool GooglePlayServices::IsSignedIn()
	{
		return m_pEnv->CallBooleanMethod( m_pObj, m_hIsSignedInMethod );
	}

	void GooglePlayServices::ShowAlert( const char* pMessageString )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pMessageString );
		m_pEnv->CallVoidMethod( m_pObj, m_hShowAlertMethod, jStringMessage );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GooglePlayServices::ShowAlert( const char* pTitleString, const char* pMessageString )
	{
		jstring jStringTitle = m_pEnv->NewStringUTF( pTitleString );
		jstring jStringMessage = m_pEnv->NewStringUTF( pMessageString );
		m_pEnv->CallVoidMethod( m_pObj, m_hShowAlertWithTitleMethod, jStringTitle, jStringMessage );
		m_pEnv->DeleteLocalRef( jStringMessage );
		m_pEnv->DeleteLocalRef( jStringTitle );
	}
} /* namespace Android */

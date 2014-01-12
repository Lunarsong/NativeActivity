/*
 * GooglePlayServices.h
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#pragma once

#include <jni.h>

namespace Android
{
	class GooglePlayServices
	{
	public:
		static void SignIn();
		static void SignOut();
		static bool IsSignedIn();
		static void ShowAlert( const char* pMessageString );
		static void ShowAlert( const char* pTitleString, const char* pMessageString );

	private:
		static jmethodID m_hGetGamesClientMethod;
		static jmethodID m_hGetAppStateClientMethod;
		static jmethodID m_hGetPlusClientMethod;

		static jmethodID m_hIsSignedInMethod; 					// bool isSignedIn()
		static jmethodID m_hBeginUserInitiatedSignInMethod; 	// void beginUserInitiatedSignIn()
		static jmethodID m_hSignOutMethod;						// void signOut();
		static jmethodID m_hShowAlertMethod;					// void showAlert( String message )
		static jmethodID m_hShowAlertWithTitleMethod;			// void showAlert( String title, String message )
		static jmethodID m_hEnableDebugLogMethod;				// void enableDebugLog( boolean enable, String tag )
		static jmethodID m_hGetInvitationIDMethod;				// String getInvitationId()
		static jmethodID m_hReconnectClientsMethod;				// void reconnectClients( int iWhichClients );
		static jmethodID m_hGetScopesMethod;					// String getScopes()
		static jmethodID m_hGetScopesArrayMethod;				// String[] getScopesArray()
		static jmethodID m_hHasSignInErrorMethod;				// bool hasSignInError()
		static jmethodID m_hGetSignInErrorMethod;				// GameHelper.SignInFailureReason getSignInError()

		// Environment
		static JNIEnv* 	m_pEnv;
		static jobject 	m_pObj;
		static jclass	m_jClass;
		static void Init( JNIEnv* pEnv, jobject pObj );

		friend class NativeActivity;
	};

} /* namespace Android */

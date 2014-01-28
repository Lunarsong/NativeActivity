/*
 * GooglePlus.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#include "GooglePlus.h"
#include "AndroidLog.h"

namespace Android
{
	// Methods
	jmethodID GooglePlus::m_hLoadPeopleMethod = NULL;
	jmethodID GooglePlus::m_hLoadVisiblePeopleMethod = NULL;
	jmethodID GooglePlus::m_hLoadOnlinePeopleMethod = NULL;
	jmethodID GooglePlus::m_hGetCurrentPersonMethod = NULL;

	jmethodID GooglePlus::m_hShareMethod = NULL;

	// Environment
	JNIEnv* GooglePlus::m_pEnv 		= NULL;
	jobject GooglePlus::m_pObj 		= NULL;


	/*
	 * PlusShare
	 */
	/*void GooglePlus::PlusShare::SetText( const char* pText )
	{

	}

	void GooglePlus::PlusShare::SetURL( const char* pURL )
	{

	}

	void GooglePlus::LoadPeople( const char** arrPeopleIDs, unsigned int uiNumPeople, IOnPeopleLoaderListener* pDelegate )
	{

	}

	void GooglePlus::LoadVisiblePeople( IOnPeopleLoaderListener* pDelegate )
	{

	}

	void GooglePlus::LoadOnlinePeople( IOnPeopleLoaderListener* pDelegate )
	{

	}

	void GooglePlus::Share( const PlusShare& item )
	{

	}*/
	void GooglePlus::Init( JNIEnv* pEnv, jobject pObj, jclass hClass )
	{
		LOGV( "Initialising GooglePlus" );
		m_pEnv = pEnv;
		m_pObj = pObj;

		/*
		m_hGetCurrentPersonMethod   = m_pEnv->GetMethodID( hClass, "LoadOnlinePeople", "()V" );

		m_hLoadPeopleMethod			= m_pEnv->GetMethodID( hClass, "LoadOnlinePeople", "()V" );
		m_hLoadVisiblePeopleMethod	= m_pEnv->GetMethodID( hClass, "GetCurrentPerson", "(Ljava/lang/String;)V" );
		m_hLoadOnlinePeopleMethod	= m_pEnv->GetMethodID( hClass, "showAlert", "(Ljava/lang/String;Ljava/lang/String;)V" );

		m_hShareMethod 				= m_pEnv->GetMethodID( hClass, "hasSignInError", "()Z" );*/
	}

} /* namespace Android */

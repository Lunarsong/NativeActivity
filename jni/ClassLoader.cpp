/*
 * ClassLoader.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#include "ClassLoader.h"

namespace Android
{

	ClassLoader::ClassLoader()
	{
		m_pEnv				= NULL;
		m_hClass			= NULL;
		m_pObject			= NULL;

		m_hFindClassMethod	= NULL;
	}

	void ClassLoader::InitJNI( JNIEnv* pEnv, jclass hActivityClass, jobject pActivityObject )
	{
		m_pEnv = pEnv;
		m_hClass = pEnv->FindClass( "java/lang/ClassLoader" );
		m_hFindClassMethod = pEnv->GetMethodID( m_hClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;" );

		jmethodID hGetClassLoader = pEnv->GetMethodID( hActivityClass, "getClassLoader", "()Ljava/lang/ClassLoader;" );
		m_pObject = pEnv->CallObjectMethod( pActivityObject, hGetClassLoader );
		pEnv->NewGlobalRef( m_pObject );
	}

	ClassLoader::~ClassLoader()
	{
		if ( m_pObject )
		{
			m_pEnv->DeleteGlobalRef( m_pObject );
		}
	}

	jclass ClassLoader::FindClass( const char* pClassName )
	{
		jstring string = m_pEnv->NewStringUTF( pClassName );

		jclass result = (jclass)m_pEnv->CallObjectMethod( m_pObject, m_hFindClassMethod, string );

		m_pEnv->DeleteLocalRef( string );

		return result;
	}

} /* namespace Android */

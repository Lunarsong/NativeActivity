/*
 * Asset.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#include "Asset.h"
#include "AndroidLog.h"

namespace Android
{
	JNIEnv*		Asset::s_pEnv = NULL;
	jclass		Asset::s_pClass = NULL;
	jmethodID	Asset::s_hReadMethod = NULL;
	jmethodID	Asset::s_hSkipMethod = NULL;
	jmethodID	Asset::s_hCloseMethod = NULL;

	void Asset::Init( JNIEnv* pEnv )
	{
		s_pEnv = pEnv;

		// Get the class
		s_pClass = pEnv->FindClass( "java/io/InputStream" );

		// Get the methods
		s_hSkipMethod = pEnv->GetMethodID( s_pClass, "skip", "(J)J" );
		s_hCloseMethod = pEnv->GetMethodID( s_pClass, "close", "()V" );
		s_hReadMethod = pEnv->GetMethodID( s_pClass, "read", "([BII)I" );
	}

	Asset::Asset( const char* pFilename, jobject pReaderObject, size_t lSize )
	{
		m_Filename = pFilename;
		m_pObject = s_pEnv->NewGlobalRef( pReaderObject );

		m_lSize = lSize;
		m_lBufferPosition = 0;
	}

	Asset::~Asset()
	{
		s_pEnv->CallVoidMethod( m_pObject, s_hCloseMethod );
		s_pEnv->DeleteGlobalRef( m_pObject );
	}

	long Asset::Size() const
	{
		return m_lSize;
	}

	long Asset::Read( char* pBuffer, long lBytesToRead ) // returns bytes read
	{
		// Create java byte array
		jbyteArray arrBytes = s_pEnv->NewByteArray( lBytesToRead );

		// Read bytes
		long lBytesRead = (long)s_pEnv->CallLongMethod( m_pObject, s_hReadMethod, arrBytes, 0, (int)lBytesToRead );

		// Retrieve bytes from array
		jbyte* pBytes = s_pEnv->GetByteArrayElements( arrBytes, NULL );

		// Copy bytes to user buffer
		memcpy( pBuffer, pBytes, lBytesRead );

		// Release bytes and bytes array
		s_pEnv->ReleaseByteArrayElements( arrBytes, pBytes, 0 );
		s_pEnv->DeleteLocalRef( arrBytes );

		// Increment position
		m_lBufferPosition += lBytesRead;

		return lBytesRead;
	}

	long Asset::Position() const // returns buffer position
	{
		return m_lBufferPosition;
	}
}

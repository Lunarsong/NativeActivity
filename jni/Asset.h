/*
 * Asset.h
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#ifndef ASSET_H_
#define ASSET_H_

#include <jni.h>

namespace Android
{
	class Asset
	{
	public:
		virtual ~Asset();

		unsigned long Size() const;
		unsigned long Read( char* pBuffer, long lBytesToRead ); // returns bytes read

		unsigned long Position() const; // returns buffer position

	private:
		unsigned long 	m_ulSize;
		unsigned long	m_ulBufferPosition;

		Asset( const char* pFilename, jobject pReaderObject, unsigned long ulSize );

		static void Init( JNIEnv* pEnv );

		// JNI
		jobject m_pObject;

		// static JNI
		static JNIEnv*		s_pEnv;
		static jclass		s_pClass;
		static jmethodID	s_hReadMethod;
		static jmethodID	s_hSkipMethod;
		static jmethodID	s_hCloseMethod;

		friend class AssetManager;
	};
}

#endif /* ASSET_H_ */

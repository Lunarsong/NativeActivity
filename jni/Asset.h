/*
 * Asset.h
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#ifndef ASSET_H_
#define ASSET_H_

#include <string>
#include <jni.h>

namespace Android
{
	class Asset
	{
	public:
		virtual ~Asset();

		long Size() const;
		long Read( char* pBuffer, long lBytesToRead ); // returns bytes read

		long Position() const; // returns buffer position

	private:
		std::string m_Filename;
		long 	m_lSize;
		long	m_lBufferPosition;

		Asset( const char* pFilename, jobject pReaderObject, size_t lSize );

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

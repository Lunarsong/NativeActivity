/*
 * AssetManager.h
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#include <jni.h>

#include "Asset.h"
#include "Paths.h"

namespace Android
{
	class NativeActivity;
	class AssetManager
	{
	public:
		virtual ~AssetManager();

		Paths* GetAssetsAtPath( const char* strPath ) const;	// fills "out" with files at "strPath"
		unsigned long GetAssetSize( const char* strFile ) const;
		Asset* GetAsset( const char* strFile ) const;

	private:
		AssetManager( NativeActivity* pNativeActivity );
		void Init();

		// Members
		NativeActivity* m_pNativeActivity;
		JNIEnv* m_pEnv;
		jobject m_pObject;

		// Java methods
		jmethodID m_hGetAssetsAtPath;
		jmethodID m_hGetAssetSize;
		jmethodID m_hGetAsset;

		friend class NativeActivity;

		unsigned long GetAssetSize( jstring strFilename ) const;
	};
}

#endif /* ASSETMANAGER_H_ */

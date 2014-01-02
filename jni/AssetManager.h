/*
 * AssetManager.h
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#include <jni.h>

#include <vector>
#include <string>

#include "Asset.h"

namespace Android
{
	class NativeActivity;
	class AssetManager
	{
	public:
		virtual ~AssetManager();

		size_t GetAssetsAtPath( const char* strPath, std::vector< std::string >& out ) const;	// fills "out" with files at "strPath"
		size_t GetAssetSize( const char* strFile ) const;
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

		size_t GetAssetSize( jstring strFilename ) const;
	};
}

#endif /* ASSETMANAGER_H_ */

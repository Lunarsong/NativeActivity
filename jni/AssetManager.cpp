/*
 * AssetManager.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#include "AssetManager.h"
#include "NativeActivity.h"
#include "AndroidLog.h"
namespace Android
{
	AssetManager::AssetManager( NativeActivity* pNativeActivity )
	{
		m_pNativeActivity = pNativeActivity;

		m_pEnv = NULL;
		m_pObject = NULL;

		// Java methods
		m_hGetAssetsAtPath = NULL;
		m_hGetAssetSize = NULL;
		m_hGetAsset = NULL;
	}

	AssetManager::~AssetManager()
	{

	}

	void AssetManager::Init()
	{
		// Save JNI variables
		m_pEnv = m_pNativeActivity->GetJNI();
		m_pObject = m_pNativeActivity->GetObject();
		jclass pClass = m_pNativeActivity->GetClass();

		// Retrieve method IDs
		m_hGetAssetsAtPath = m_pEnv->GetMethodID( pClass, "getAssetsAtPath", "(Ljava/lang/String;)[Ljava/lang/String;" );
		m_hGetAssetSize = m_pEnv->GetMethodID( pClass, "getAssetSize", "(Ljava/lang/String;)J" );
		m_hGetAsset = m_pEnv->GetMethodID( pClass, "getAsset", "(Ljava/lang/String;)Ljava/io/InputStream;" );

		// Init asset class
		Asset::Init( m_pEnv );

	}

	size_t AssetManager::GetAssetsAtPath( const char* strPath, std::vector< std::string >& out ) const
	{
		//LOGV( "[GetAssetsAtPath] Looking up path: %s.", strPath );

		size_t lArrayLength = 0;
		out.clear();

		jstring jStringPath = m_pEnv->NewStringUTF( strPath );
		jobjectArray jArray = (jobjectArray)m_pEnv->CallObjectMethod( m_pObject, m_hGetAssetsAtPath, jStringPath );
		m_pEnv->DeleteLocalRef( jStringPath );
		if ( jArray )
		{
			lArrayLength = m_pEnv->GetArrayLength( jArray );
			if ( lArrayLength > out.capacity() )
			{
				out.reserve( lArrayLength );
			}

			//LOGV( "Paths Array Length: %i ", pEnv->GetArrayLength( jArray ) );

			for ( size_t i = 0; i < lArrayLength; ++i )
			{
				jstring strFile = (jstring)m_pEnv->GetObjectArrayElement( jArray, i );
				const char* pFileString = m_pEnv->GetStringUTFChars( strFile, NULL );

				//LOGV( "%s", pFileString );

				out.push_back( pFileString );

				m_pEnv->ReleaseStringUTFChars( strFile, pFileString );
			}
		}

		return lArrayLength;
	}

	size_t AssetManager::GetAssetSize( const char* strFile ) const
	{
		jstring jStringPath = m_pEnv->NewStringUTF( strFile );
		long lFileSize = m_pEnv->CallLongMethod( m_pObject, m_hGetAssetSize, jStringPath );
		m_pEnv->DeleteLocalRef( jStringPath );

		//LOGV( "[AssetManager] GetAssetSize: (%s, %ld)", strFile, lFileSize );

		return lFileSize;
	}

	size_t AssetManager::GetAssetSize( jstring strFilename ) const
	{
		long lFileSize = m_pEnv->CallLongMethod( m_pObject, m_hGetAssetSize, strFilename );

		//LOGV( "[AssetManager] _GetAssetSize: (%ld)", lFileSize );

		return lFileSize;
	}

	Asset* AssetManager::GetAsset( const char* strFile ) const
	{
		// Create java string
		jstring jStringPath = m_pEnv->NewStringUTF( strFile );

		// Retrieve file size and see if it is non zero
		size_t lAssetSize = GetAssetSize( jStringPath );
		if ( lAssetSize <= 0 )
		{
			m_pEnv->DeleteLocalRef( jStringPath );
			return NULL;
		}

		// Retrieve file
		jobject pAssetObject = m_pEnv->CallObjectMethod( m_pObject, m_hGetAsset, jStringPath );

		// Delete java string
		m_pEnv->DeleteLocalRef( jStringPath );

		if ( !pAssetObject )
		{
			return NULL;
		}

		// Create the asset
		Asset* pAsset = new Asset( strFile, pAssetObject, lAssetSize );

		return pAsset;
	}
}

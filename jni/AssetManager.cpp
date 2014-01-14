/*
 * AssetManager.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: Nishry
 */

#include "AssetManager.h"
#include "NativeActivity.h"
#include "AndroidLog.h"

#include <string.h>

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

	Paths* AssetManager::GetAssetsAtPath( const char* strPath ) const
	{
		//LOGV( "[GetAssetsAtPath] Looking up path: %s.", strPath );
		Paths* pPaths = NULL; // return value
		size_t lArrayLength = 0;

		// Create the path string to retrieve paths from
		jstring jStringPath = m_pEnv->NewStringUTF( strPath );

		// Call function
		jobjectArray jArray = (jobjectArray)m_pEnv->CallObjectMethod( m_pObject, m_hGetAssetsAtPath, jStringPath );

		// Release string
		m_pEnv->DeleteLocalRef( jStringPath );

		if ( jArray )
		{
			// Get the number of paths retrieved
			lArrayLength = m_pEnv->GetArrayLength( jArray );
			if ( lArrayLength > 0 )
			{
				// Create the paths array
				char** pPathsArray = new char* [ lArrayLength ];

				//LOGV( "Paths Array Length: %i ", pEnv->GetArrayLength( jArray ) );

				// Copy the paths' strings
				for ( size_t i = 0; i < lArrayLength; ++i )
				{
					// Get the current path's string
					jstring strFile = (jstring)m_pEnv->GetObjectArrayElement( jArray, i );
					const char* pFileString = m_pEnv->GetStringUTFChars( strFile, NULL );

					//LOGV( "%s", pFileString );

					// String's size
					size_t lStringLength = m_pEnv->GetStringLength( strFile );

					// Create a copy c string
					pPathsArray[ i ] = new char [ lStringLength + 1 ];
					memcpy( pPathsArray[ i ], pFileString, lStringLength );

					// Null terminating character
					pPathsArray[ i ][ lStringLength ] = 0;

					// Release the string
					m_pEnv->ReleaseStringUTFChars( strFile, pFileString );
				}

				// Create the paths class
				pPaths = new Paths( pPathsArray, lArrayLength );
			}
		}

		return pPaths;
	}

	unsigned long AssetManager::GetAssetSize( const char* strFile ) const
	{
		jstring jStringPath = m_pEnv->NewStringUTF( strFile );
		unsigned long lFileSize = m_pEnv->CallLongMethod( m_pObject, m_hGetAssetSize, jStringPath );
		m_pEnv->DeleteLocalRef( jStringPath );

		//LOGV( "[AssetManager] GetAssetSize: (%s, %ld)", strFile, lFileSize );

		return lFileSize;
	}

	unsigned long AssetManager::GetAssetSize( jstring strFilename ) const
	{
		unsigned long lFileSize = m_pEnv->CallLongMethod( m_pObject, m_hGetAssetSize, strFilename );

		//LOGV( "[AssetManager] _GetAssetSize: (%ld)", lFileSize );

		return lFileSize;
	}

	Asset* AssetManager::GetAsset( const char* strFile ) const
	{
		// Create java string
		jstring jStringPath = m_pEnv->NewStringUTF( strFile );

		// Retrieve file size and see if it is non zero
		unsigned long lAssetSize = GetAssetSize( jStringPath );
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

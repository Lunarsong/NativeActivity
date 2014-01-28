/*
 * GooglePlus.h
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#pragma once

#include <jni.h>

namespace Android
{
	class GooglePlus
	{
	public:
		enum ConnectionResult
		{
			/*
			 * Error Codes:
			 * http://developer.android.com/reference/com/google/android/gms/common/ConnectionResult.html
			 */

			SUCCESS 							= 0,
			DATA_INVALID 						= 12,
			DEVELOPER_ERROR 					= 10,
			INTERNAL_ERROR 						= 8,
			INVALID_ACCOUNT 					= 5,
			LICENSE_CHECK_FAILED 				= 11,
			NETWORK_ERROR 						= 7,
			RESOLUTION_REQUIRED					= 6,
			SERVICE_DISABLED					= 3,
			SERVICE_INVALID						= 9,
			SERVICE_MISSING						= 1,
			SERVICE_VERSION_UPDATE_REQUIRED		= 2,
			SIGN_IN_REQUIRED					= 4
		};

		struct Person
		{

		};

		class IOnPeopleLoaderListener
		{
			virtual void OnPeopleLoaded( ConnectionResult eResult, Person** arrPeople, unsigned int uiNumPeople, const char* pNextPageToken ) = 0;
		};

		class PlusShare
		{
			void SetText( const char* pText );
			void SetURL( const char* pURL );
		};

		/*static const Person* GetCurrentPerson();

		static void LoadPeople( const char** arrPeopleIDs, unsigned int uiNumPeople, IOnPeopleLoaderListener* pDelegate );
		static void LoadVisiblePeople( IOnPeopleLoaderListener* pDelegate );
		static void LoadOnlinePeople( IOnPeopleLoaderListener* pDelegate );

		static void Share( const PlusShare& item );*/

	private:
		// Methods
		static jmethodID m_hGetCurrentPersonMethod;

		static jmethodID m_hLoadPeopleMethod;
		static jmethodID m_hLoadVisiblePeopleMethod;
		static jmethodID m_hLoadOnlinePeopleMethod;

		static jmethodID m_hShareMethod;

		// Environment
		static JNIEnv* 	m_pEnv;
		static jobject 	m_pObj;

		static void Init( JNIEnv* pEnv, jobject pObj, jclass hClass );

		friend class GooglePlayServices;
		friend class NativeActivity;
	};

} /* namespace Android */

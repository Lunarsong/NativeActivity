/*
 * AppState.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: Shanee
 */

#include "AppState.h"

namespace Android
{
	JNIEnv* 	AppState::m_pEnv 	= NULL;
	jobject 	AppState::m_pObj	= NULL;

	//
	jfieldID  	AppState::m_hCloudSaveHelperField	= NULL;
	jclass 		AppState::m_hCloudSaveHelperClass	= NULL;

	// Methods
	jmethodID 	AppState::m_hUpdateStateMethod 			= NULL;
	jmethodID 	AppState::m_hUpdateStateImmediateMethod = NULL;
	jmethodID 	AppState::m_hLoadStateMethod			= NULL;
	jmethodID 	AppState::m_hResolveStateMethod			= NULL;

	void AppState::Init( JNIEnv* pEnv, jobject pObj )
	{
		m_pEnv = pEnv;
		m_pObj = pObj;

		// Retrieve the helper class field
		jclass jNativeGameActivity = pEnv->FindClass( "com/lunarsong/android/NativeGameActivity" );
		m_hCloudSaveHelperField = pEnv->GetFieldID( jNativeGameActivity, "mCloudSaveHelper", "Lcom/lunarsong/android/CloudSaveHelper;" );

		// Save the helper class type
		m_hCloudSaveHelperClass = pEnv->FindClass( "com/lunarsong/android/CloudSaveHelper" );

		// Retrieve methods
		m_hUpdateStateMethod 			= pEnv->GetMethodID( m_hCloudSaveHelperClass, "updateState", "(I[B)V" );
		m_hUpdateStateImmediateMethod 	= pEnv->GetMethodID( m_hCloudSaveHelperClass, "updateStateImmediate", "(Ljava/lang/Object;I[B)V" );
		m_hLoadStateMethod			 	= pEnv->GetMethodID( m_hCloudSaveHelperClass, "loadState", "(Ljava/lang/Object;I)V" );
		m_hResolveStateMethod			= pEnv->GetMethodID( m_hCloudSaveHelperClass, "resolveState", "(Ljava/lang/Object;ILjava/lang/String;[B)V" );
	}

	void AppState::UpdateState( int iStateKey, const char* pData, unsigned int uiDataSize )
	{
		jobject pCloudHelper = m_pEnv->GetObjectField( m_pObj, m_hCloudSaveHelperField );
		jbyteArray arrData = m_pEnv->NewByteArray( uiDataSize );

		m_pEnv->SetByteArrayRegion( arrData, 0, uiDataSize, (const signed char*)pData );

		m_pEnv->CallVoidMethod( pCloudHelper, m_hUpdateStateMethod, iStateKey, arrData );
	}

	void AppState::UpdateStateImmediate( int iStateKey, const char* pData, unsigned int uiDataSize, IAppStateListener* pStateListener )
	{
		jobject pCloudHelper = m_pEnv->GetObjectField( m_pObj, m_hCloudSaveHelperField );
		jbyteArray arrData = m_pEnv->NewByteArray( uiDataSize );

		m_pEnv->SetByteArrayRegion( arrData, 0, uiDataSize, (const signed char*)pData );

		jobject pListener = m_pEnv->NewDirectByteBuffer( pStateListener, sizeof( IAppStateListener* ) );
		m_pEnv->CallVoidMethod( pCloudHelper, m_hUpdateStateImmediateMethod, pListener, iStateKey, arrData );
	}

	void AppState::LoadState( int iStateKey, IAppStateListener* pStateListener )
	{
		jobject pCloudHelper = m_pEnv->GetObjectField( m_pObj, m_hCloudSaveHelperField );

		jobject pListener = m_pEnv->NewDirectByteBuffer( pStateListener, sizeof( IAppStateListener* ) );
		m_pEnv->CallVoidMethod( pCloudHelper, m_hLoadStateMethod, pListener, iStateKey );
	}

	void AppState::ResolveState( const int iStateKey, const jstring resolvedVersion, const AppStateData* pResolvedData, const jobject pStateListener )
	{
		jobject pCloudHelper = m_pEnv->GetObjectField( m_pObj, m_hCloudSaveHelperField );

		jbyteArray arrData = m_pEnv->NewByteArray( pResolvedData->Size() );
		m_pEnv->SetByteArrayRegion( arrData, 0, pResolvedData->Size(), (const signed char*)pResolvedData->Data() );

		m_pEnv->CallVoidMethod( pCloudHelper, m_hResolveStateMethod, pStateListener, iStateKey, resolvedVersion, arrData );
	}

	AppStateData::AppStateData()
	{
		mData 	= NULL;
		mSize	= 0;
	}

	AppStateData::AppStateData( const char* pData, unsigned int uiDataSize )
	{
		SetData( pData, uiDataSize );
	}

	AppStateData::~AppStateData()
	{

	}

	void AppStateData::SetData( const char* pData, unsigned int uiDataSize )
	{
		mData = pData;
		mSize = uiDataSize;
	}

	unsigned int AppStateData::Size() const
	{
		return mSize;
	}

	const char* AppStateData::Data() const
	{
		return mData;
	}

} /* namespace Android */

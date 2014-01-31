/*
 * AppStateImpl.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: Shanee
 */

#include "AppStateImpl.h"
#include "Android.h"
#include "AppState.h"
#include "AndroidLog.h"

namespace Android
{
	AppStateImpl::AppStateImpl( JNIEnv* pEnv )
	{
		m_pEnv = pEnv;
	}

	AppStateImpl::~AppStateImpl()
	{

	}

	void AppStateImpl::OnStateLoaded( const jobject pListener, const int iStatusCode, const int iStateKey, const jbyteArray data )
	{
		if ( data )
		{
			jbyte* pBytes = m_pEnv->GetByteArrayElements( data, NULL );
			jsize arraySize = m_pEnv->GetArrayLength( data );

			if ( pListener )
			{
				AppStateData stateData( (const char*)pBytes, arraySize );

				IAppStateListener* pStateListener = (IAppStateListener*)m_pEnv->GetDirectBufferAddress( pListener );
				pStateListener->OnStateLoaded( iStatusCode, iStateKey, &stateData );
			}

			m_pEnv->ReleaseByteArrayElements( data, pBytes, JNI_ABORT );
		}
	}

	void AppStateImpl::OnStateConflict( const jobject pListener, const int iStateKey, const jstring resolvedVersion, const jbyteArray localData, const jbyteArray serverData )
	{
		if ( pListener )
		{
			// Get the local state buffer
			jbyte* pLocalBytes = m_pEnv->GetByteArrayElements( localData, NULL );
			jsize jLocalArraySize = m_pEnv->GetArrayLength( localData );

			// Get the server state buffer
			jbyte* pServerBytes = m_pEnv->GetByteArrayElements( serverData, NULL );
			jsize jServerArraySize = m_pEnv->GetArrayLength( serverData );

			// Create classes
			AppStateData localStateData( (const char*)pLocalBytes, jLocalArraySize );
			AppStateData serverStateData( (const char*)pServerBytes, jServerArraySize );
			AppStateData resolvedState;

			// Call listener
			IAppStateListener* pStateListener = (IAppStateListener*)m_pEnv->GetDirectBufferAddress( pListener );
			pStateListener->OnStateConflict( iStateKey, &localStateData, &serverStateData, &resolvedState );
			AppState::ResolveState( iStateKey, resolvedVersion, &resolvedState, pListener );

			// Release buffers
			m_pEnv->ReleaseByteArrayElements( localData, pLocalBytes, JNI_ABORT );
			m_pEnv->ReleaseByteArrayElements( serverData, pServerBytes, JNI_ABORT );
		}
	}

} /* namespace Android */

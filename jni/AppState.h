/*
 * AppState.h
 *
 *  Created on: Jan 27, 2014
 *      Author: Shanee
 */

#ifndef APPSTATE_H_
#define APPSTATE_H_

#include <JNI.h>

namespace Android
{
	enum AppStateResult
	{
		STATUS_OK,
		STATUS_NETWORK_ERROR_NO_DATA,
		STATUS_NETWORK_ERROR_STALE_DATA,
		STATUS_CLIENT_RECONNECT_REQUIRED,
		STATUS_INTERNAL_ERROR,
		STATUS_STATE_KEY_NOT_FOUND,
		STATUS_STATE_KEY_LIMIT_EXCEEDED
	};

	class AppStateData
	{
	public:
		AppStateData();
		AppStateData( const char* pData, unsigned int uiDataSize );
		~AppStateData();

		void SetData( const char* pData, unsigned int uiDataSize );
		unsigned int Size() const;
		const char* Data() const;

	private:
		const char*	 mData;
		unsigned int mSize;
	};

	class IAppStateListener
	{
	public:
		virtual void OnStateLoaded( int iStatusCode, int iStateKey, const AppStateData* pData ) = 0;
		virtual void OnStateConflict( int iStateKey, const AppStateData* pLocaData,
										const AppStateData* pServerData, AppStateData* pResolvedData ) = 0;

		virtual ~IAppStateListener() { }
	};

	class AppState
	{
	public:
		// iStateKey is a save slot indicator.
		// iStateKey must be smaller than GetMaxStatesNum's return.
		static void UpdateState( int iStateKey, const char* pData, unsigned int uiDataSize );
		static void UpdateStateImmediate( int iStateKey, const char* pData, unsigned int uiDataSize, IAppStateListener* pStateListener );
		static void LoadState( int iStateKey, IAppStateListener* pStateListener );

		/*static int GetMaxStatesNum(); // Returns the number of states allowed
		static int GetMaxStateSize(); // Returns the maximum state size allowed to save*/

	private:
		static JNIEnv* m_pEnv;
		static jobject m_pObj;

		//
		static jfieldID  m_hCloudSaveHelperField;
		static jclass m_hCloudSaveHelperClass;

		// Methods
		static jmethodID m_hUpdateStateMethod;
		static jmethodID m_hUpdateStateImmediateMethod;
		static jmethodID m_hLoadStateMethod;
		static jmethodID m_hResolveStateMethod;

		static void Init( JNIEnv* pEnv, jobject pObj );

		friend class GooglePlayServices;
		friend class AppStateImpl;

		static void ResolveState( const int iStateKey, const jstring resolvedVersion, const AppStateData* pResolvedData, const jobject pStateListener );

	};
} /* namespace Android */


#endif /* APPSTATE_H_ */

/*
 * AppState.h
 *
 *  Created on: Jan 27, 2014
 *      Author: Shanee
 */

#ifndef APPSTATE_H_
#define APPSTATE_H_

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
		/*AppStateData();
		~AppStateData();

		void SetData( const char* pData, unsigned int uiDataSize );
		unsigned int Size() const;
		const char* Data() const;*/

	private:
		char*		 mData;
		unsigned int mSize;
	};

	class IAppStateListener
	{
	public:
		virtual void OnStateLoaded( int iStatusCode, int iStateKey, const AppStateData* pData ) = 0;
		virtual void OnStateSaved( int iStatusCode, int iStateKey ) = 0;
		virtual void OnStateConflict( int iStateKey, const AppStateData* pLocaData,
										const AppStateData* pServerData, AppStateData* pResolvedData );

		virtual ~IAppStateListener() { }
	};

	class AppState
	{
	public:
		// iStateKey is a save slot indicator.
		// iStateKey must be smaller than GetMaxStatesNum's return.
		/*static void UpdateState( int iStateKey, const char* pData, unsigned int uiDataSize );
		static void UpdateStateImmediate( int iStateKey, const char* pData, unsigned int uiDataSize, IAppStateListener* pStateListener );
		static void LoadState( int iStateKey, IAppStateListener* pStateListener );

		static int GetMaxStatesNum(); // Returns the number of states allowed
		static int GetMaxStateSize(); // Returns the maximum state size allowed to save*/

	private:

	};
} /* namespace Android */


#endif /* APPSTATE_H_ */

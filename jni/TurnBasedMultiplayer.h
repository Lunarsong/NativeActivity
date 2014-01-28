/*
 * TurnBasedMultiplayer.h
 *
 *  Created on: Jan 27, 2014
 *      Author: Shanee
 */

#ifndef TURNBASEDMULTIPLAYER_H_
#define TURNBASEDMULTIPLAYER_H_

namespace Android
{

	class TurnBasedMultiplayer
	{
	public:
		class IPlayersSelectedListener;
		class ITurnBasedMatchInitiatedListener;
		class TurnBasedMatch;

		/*static void OpenPlayersSelection( int iMinPlayers, int iMaxPlayers, bool bAllowAutoMatch, IPlayersSelectedListener* pListener );

		static void CreateTurnBasedMatch( void* pPlayers, ITurnBasedMatchInitiatedListener* pListener );
		static void CreateTurnBasedAutoMatch( int iMinPlayers, int iMaxPlayers, ITurnBasedMatchInitiatedListener* pListener );
		static void CreateTurnBasedAutoMatch( int iMinPlayers, int iMaxPlayers, ITurnBasedMatchInitiatedListener* pListener, int iVariant ); // iVariant must be 1-1023 (inclusive) or -1 for any

		static void AcceptInvitation( const char* pInvitationID, ITurnBasedMatchInitiatedListener* pListener );
		static void DeclineInvitation( const char* pInvitationID );
		static void DismissInvitation( const char* pInvitationID );*/

		class IPlayersSelectedListener
		{
		public:
			virtual void OnPlayersSelected() = 0;
			virtual void OnPlayersSelectionCancel() = 0;

			virtual ~IPlayersSelectedListener() { }
		};

		class TurnBasedMatch
		{
			public:
		};

		enum StatusCode
		{
			// https://developer.android.com/reference/com/google/android/gms/games/multiplayer/turnbased/OnTurnBasedMatchInitiatedListener.html

			STATUS_OK										= 0,
			STATUS_MATCH_ERROR_ALREADY_REMATCHED			= 6505,
			STATUS_NETWORK_ERROR_OPERATION_FAILED			= 6,
			STATUS_MULTIPLAYER_ERROR_NOT_TRUSTED_TESTER 	= 6001,
			STATUS_MULTIPLAYER_ERROR_INVALID_OPERATION		= 6004,
			STATUS_MULTIPLAYER_DISABLED						= 6003,
			STATUS_CLIENT_RECONNECT_REQUIRED				= 2,
			STATUS_INTERNAL_ERROR							= 1
		};

		class ITurnBasedMatchInitiatedListener
		{
			virtual void OnTurnBasedMatchInitiated( StatusCode eStatus, TurnBasedMatch* pMatch ) = 0;
		};
	};

} /* namespace Android */
#endif /* TURNBASEDMULTIPLAYER_H_ */

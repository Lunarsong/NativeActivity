/*
 * GoogleGames.cpp
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#include "GoogleGames.h"

namespace Android
{
	JNIEnv* GoogleGames::m_pEnv 					= NULL;
	jobject GoogleGames::m_pObj						= NULL;

	jmethodID GoogleGames::m_hShowLeaderboard 		= NULL;
	jmethodID GoogleGames::m_hShowAllLeaderboards	= NULL;
	jmethodID GoogleGames::m_hShowAchievements		= NULL;

	jmethodID GoogleGames::m_hSubmitScore			= NULL;	// void submitScore( String leaderboardId, long score )
	jmethodID GoogleGames::m_hUnlockAchievement		= NULL;	// void unlockAchievement( String id )
	jmethodID GoogleGames::m_hIncrementAchievement	= NULL;	// void incrementAchievement( String id, int numSteps )
	jmethodID GoogleGames::m_hSetAchievementSteps	= NULL;	// void setAchievementSteps( String id, int numSteps )
	jmethodID GoogleGames::m_hRevealAchievement		= NULL;	// void revealAchievement( String id )

	void GoogleGames::ShowLeaderboard( const char* pLeaderboardString )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pLeaderboardString );
		m_pEnv->CallVoidMethod( m_pObj, m_hShowLeaderboard, jStringMessage );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::ShowAllLeaderboards()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hShowAllLeaderboards );
	}

	void GoogleGames::ShowAchievements()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hShowAchievements );
	}

	void GoogleGames::SubmitScore( const char* pLeaderboardString, long long lScore )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pLeaderboardString );
		m_pEnv->CallVoidMethod( m_pObj, m_hSubmitScore, jStringMessage, lScore );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::UnlockAchievement( const char* pAchievementString )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pAchievementString );
		m_pEnv->CallVoidMethod( m_pObj, m_hUnlockAchievement, jStringMessage );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::RevealAchievement( const char* pAchievementString )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pAchievementString );
		m_pEnv->CallVoidMethod( m_pObj, m_hRevealAchievement, jStringMessage );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::IncrementAchievement( const char* pAchievementString, int iNumSteps )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pAchievementString );
		m_pEnv->CallVoidMethod( m_pObj, m_hIncrementAchievement, jStringMessage, iNumSteps );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::SetAchievementSteps( const char* pAchievementString, int iNumSteps )
	{
		jstring jStringMessage = m_pEnv->NewStringUTF( pAchievementString );
		m_pEnv->CallVoidMethod( m_pObj, m_hSetAchievementSteps, jStringMessage, iNumSteps );
		m_pEnv->DeleteLocalRef( jStringMessage );
	}

	void GoogleGames::Init( JNIEnv* pEnv, jobject pObj, jclass hClass )
	{
		m_pEnv = pEnv;
		m_pObj = pObj;

		m_hShowLeaderboard 		= m_pEnv->GetMethodID( hClass, "showLeaderboard", "(Ljava/lang/String;)V" );
		m_hShowAllLeaderboards  = m_pEnv->GetMethodID( hClass, "showAllLeaderboards", "()V" );;
		m_hShowAchievements		= m_pEnv->GetMethodID( hClass, "showAchievements", "()V" );;

		m_hSubmitScore			= m_pEnv->GetMethodID( hClass, "submitScore", "(Ljava/lang/String;J)V" );
		m_hUnlockAchievement	= m_pEnv->GetMethodID( hClass, "unlockAchievement", "(Ljava/lang/String;)V" );
		m_hIncrementAchievement	= m_pEnv->GetMethodID( hClass, "incrementAchievement", "(Ljava/lang/String;I)V" );
		m_hSetAchievementSteps	= m_pEnv->GetMethodID( hClass, "setAchievementSteps", "(Ljava/lang/String;I)V" );
		m_hRevealAchievement	= m_pEnv->GetMethodID( hClass, "revealAchievement", "(Ljava/lang/String;)V" );
	}


} /* namespace Android */

/*
 * GoogleGames.h
 *
 *  Created on: Jan 11, 2014
 *      Author: Shanee
 */

#pragma once

#include <jni.h>

namespace Android
{
	class GoogleGames
	{
	public:
		static void ShowLeaderboard( const char* pLeaderboardString );
		static void ShowAllLeaderboards();
		static void ShowAchievements();

		static void SubmitScore( const char* pLeaderboardString, long long lScore );

		static void UnlockAchievement( const char* pAchievementString );
		static void RevealAchievement( const char* pAchievementString );
		static void IncrementAchievement( const char* pAchievementString, int iNumSteps );
		static void SetAchievementSteps( const char* pAchievementString, int iNumSteps );

	private:
		static jmethodID m_hShowLeaderboard;
		static jmethodID m_hShowAllLeaderboards;
		static jmethodID m_hShowAchievements;

		static jmethodID m_hSubmitScore;			// void submitScore( String leaderboardId, long score )
		static jmethodID m_hUnlockAchievement;		// void unlockAchievement( String id )
		static jmethodID m_hIncrementAchievement;	// void incrementAchievement( String id, int numSteps )
		static jmethodID m_hSetAchievementSteps;	// void setAchievementSteps( String id, int numSteps )
		static jmethodID m_hRevealAchievement;		// void revealAchievement( String id )

		// Environment
		static JNIEnv* 	m_pEnv;
		static jobject 	m_pObj;

		static void Init( JNIEnv* pEnv, jobject pObj, jclass hClass );
		friend class GooglePlayServices;

	};

} /* namespace Android */

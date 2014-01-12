/*
 * Copyright (C) 2013 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.lunarsong.android;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.FragmentActivity;
import android.util.Log;

import com.google.android.gms.appstate.AppStateClient;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.games.GamesClient;
import com.google.android.gms.plus.PlusClient;
import com.lunarsong.android.NativeSurfaceView.NativeThread;

/**
 * Example base class for games. This implementation takes care of setting up
 * the GamesClient object and managing its lifecycle. Subclasses only need to
 * override the @link{#onSignInSucceeded} and @link{#onSignInFailed} abstract
 * methods. To initiate the sign-in flow when the user clicks the sign-in
 * button, subclasses should call @link{#beginUserInitiatedSignIn}. By default,
 * this class only instantiates the GamesClient object. If the PlusClient or
 * AppStateClient objects are also wanted, call the BaseGameActivity(int)
 * constructor and specify the requested clients. For example, to request
 * PlusClient and GamesClient, use BaseGameActivity(CLIENT_GAMES | CLIENT_PLUS).
 * To request all available clients, use BaseGameActivity(CLIENT_ALL).
 * Alternatively, you can also specify the requested clients via
 * @link{#setRequestedClients}, but you must do so before @link{#onCreate}
 * gets called, otherwise the call will have no effect.
 *
 * @author Bruno Oliveira (Google)
 */
public abstract class BaseGameActivity extends FragmentActivity implements
        GameHelper.GameHelperListener {

    // The game helper object. This class is mainly a wrapper around this object.
    protected GameHelper mHelper;
    protected Handler	 mGameHandler;

    // We expose these constants here because we don't want users of this class
    // to have to know about GameHelper at all.
    public static final int CLIENT_GAMES = GameHelper.CLIENT_GAMES;
    public static final int CLIENT_APPSTATE = GameHelper.CLIENT_APPSTATE;
    public static final int CLIENT_PLUS = GameHelper.CLIENT_PLUS;
    public static final int CLIENT_ALL = GameHelper.CLIENT_ALL;

    // Requested clients. By default, that's just the games client.
    protected int mRequestedClients = CLIENT_GAMES;

    // stores any additional scopes.
    private String[] mAdditionalScopes;

    protected String mDebugTag = "BaseGameActivity";
    protected boolean mDebugLog = false;

    /** Constructs a BaseGameActivity with default client (GamesClient). */
    protected BaseGameActivity() 
    {
        super();
        mHelper = new GameHelper(this);
        
        mGameHandler = new Handler();
    }

    /**
     * Constructs a BaseGameActivity with the requested clients.
     * @param requestedClients The requested clients (a combination of CLIENT_GAMES,
     *         CLIENT_PLUS and CLIENT_APPSTATE).
     */
    protected BaseGameActivity(int requestedClients) {
        super();
        mHelper = new GameHelper(this);
        setRequestedClients(requestedClients);
    }

    /**
     * Sets the requested clients. The preferred way to set the requested clients is
     * via the constructor, but this method is available if for some reason your code
     * cannot do this in the constructor. This must be called before onCreate in order to
     * have any effect. If called after onCreate, this method is a no-op.
     *
     * @param requestedClients A combination of the flags CLIENT_GAMES, CLIENT_PLUS
     *         and CLIENT_APPSTATE, or CLIENT_ALL to request all available clients.
     * @param additionalScopes.  Scopes that should also be requested when the auth
     *         request is made.
     */
    protected void setRequestedClients(int requestedClients, String ... additionalScopes) {
        mRequestedClients = requestedClients;
        mAdditionalScopes = additionalScopes;
    }

    @Override
    protected void onCreate(Bundle b) {
        super.onCreate(b);
        mHelper = new GameHelper(this);
        mGameHandler = new Handler();
        if (mDebugLog) {
            mHelper.enableDebugLog(mDebugLog, mDebugTag);
        }
        mHelper.setup(this, mRequestedClients, mAdditionalScopes);
    }

    @Override
    protected void onStart() {
        super.onStart();
        mHelper.onStart(this);
    }

    @Override
    protected void onStop() {
        super.onStop();
        mHelper.onStop();
    }

    @Override
    protected void onActivityResult(int request, int response, Intent data) {
        super.onActivityResult(request, response, data);
        mHelper.onActivityResult(request, response, data);
    }

    protected GamesClient getGamesClient() 
    {
        return mHelper.getGamesClient();
    }

    protected AppStateClient getAppStateClient() 
    {
        return mHelper.getAppStateClient();
    }

    protected PlusClient getPlusClient() {
        return mHelper.getPlusClient();
    }

    public boolean isSignedIn() 
    {
        return mHelper.isSignedIn();
    }

    public void beginUserInitiatedSignIn() 
    {
    	Log.e( "Native", "logging in" );
    	final Runnable r = new Runnable()
    	{
    		public void run()
    		{
    			mHelper.beginUserInitiatedSignIn();
    		}
    	};
    	
    	mGameHandler.post( r );        
    }

    public void signOut() 
    {
    	Log.e( "Native", "logging out" );
    	final Runnable r = new Runnable()
    	{
    		public void run()
    		{
    			mHelper.signOut();
    		}
    	};
    	
    	mGameHandler.post( r );
        
    }

    protected void showAlert(String title, String message) 
    {
    	class AlertRunnable implements Runnable
	    {
	        private String mTitle;
	        private String mMessage;
	        public AlertRunnable( String title, String message )
	        { 
	        	mTitle = title;
	        	mMessage = message;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	mHelper.showAlert( mTitle, mMessage );               
	        }	        
	    }
    	
    	Runnable r = new AlertRunnable( title, message );
    	mGameHandler.post( r );
    }

    protected void showAlert(String message) 
    {
    	class AlertRunnable implements Runnable
	    {
	        private String mMessage;
	        public AlertRunnable( String message )
	        { 
	        	mMessage = message;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	mHelper.showAlert( mMessage );               
	        }	        
	    }
    	
    	Runnable r = new AlertRunnable( message );
    	mGameHandler.post( r );
    }

    protected void enableDebugLog(boolean enabled, String tag) {
        mDebugLog = true;
        mDebugTag = tag;
        if (mHelper != null) {
            mHelper.enableDebugLog(enabled, tag);
        }
    }

    protected String getInvitationId() {
        return mHelper.getInvitationId();
    }

    protected void reconnectClients(int whichClients) {
        mHelper.reconnectClients(whichClients);
    }

    protected String getScopes() {
        return mHelper.getScopes();
    }

    protected String[] getScopesArray() {
        return mHelper.getScopesArray();
    }

    protected boolean hasSignInError() {
        return mHelper.hasSignInError();
    }

    protected GameHelper.SignInFailureReason getSignInError() 
    {
        return mHelper.getSignInError();
    }
    
    protected void showLeaderboard( String leaderboardID )
    {
    	class ShowLeaderboardRunnable implements Runnable
	    {
	        private String mLeaderboardID;
	        public ShowLeaderboardRunnable( String leaderboardID )
	        { 
	        	mLeaderboardID = leaderboardID;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	startActivityForResult( getGamesClient().getLeaderboardIntent( mLeaderboardID ), 0 );               
	        }	        
	    }
    
    	mGameHandler.post( new ShowLeaderboardRunnable( leaderboardID ) );
    }
    
    protected void showAllLeaderboards()
    {
    	final Runnable r = new Runnable()
    	{
    		public void run()
    		{
    			startActivityForResult( getGamesClient().getAllLeaderboardsIntent(), 0 );
    		}
    	};
    	
    	mGameHandler.post( r );
    }
    
    protected void showAchievements()
    {
    	final Runnable r = new Runnable()
    	{
    		public void run()
    		{
    			startActivityForResult( getGamesClient().getAchievementsIntent(), 0 );
    		}
    	};
    	
    	mGameHandler.post( r );
    }
    
    protected void submitScore( String leaderboardID, long lScore )
    {
    	class SubmitScoreRunnable implements Runnable
	    {
	        private String 	mLeaderboardID;
	        private long	mScore;
	        public SubmitScoreRunnable( String leaderboardID, long lScore )
	        { 
	        	mLeaderboardID 	= leaderboardID;
	        	mScore			= lScore;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	getGamesClient().submitScore( mLeaderboardID, mScore );               
	        }	        
	    }
    
    	mGameHandler.post( new SubmitScoreRunnable( leaderboardID, lScore ) );
    }
    
    protected void unlockAchievement( String achievementID )
    {
    	class UnlockAchievementRunnable implements Runnable
	    {
	        private String mAchievementID;
	        public UnlockAchievementRunnable( String achievementID )
	        { 
	        	mAchievementID = achievementID;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	getGamesClient().unlockAchievement( mAchievementID );               
	        }	        
	    }
    
    	mGameHandler.post( new UnlockAchievementRunnable( achievementID ) );
    }
    
    protected void revealAchievement( String achievementID )
    {
    	class RevealAchievementRunnable implements Runnable
	    {
	        private String mAchievementID;
	        public RevealAchievementRunnable( String achievementID )
	        { 
	        	mAchievementID = achievementID;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	getGamesClient().revealAchievement( mAchievementID );               
	        }	        
	    }
    
    	mGameHandler.post( new RevealAchievementRunnable( achievementID ) );
    }
    
    protected void incrementAchievement( String achievementID, int iNumSteps )
    {
    	class IncrementAchievementRunnable implements Runnable
	    {
	        private String 	mAchievementID;
	        private int		mNumSteps;
	        public IncrementAchievementRunnable( String achievementID, int iNumSteps )
	        { 
	        	mAchievementID 	= achievementID;
	        	mNumSteps		= iNumSteps;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	getGamesClient().incrementAchievement( mAchievementID, mNumSteps );               
	        }	        
	    }
    
    	mGameHandler.post( new IncrementAchievementRunnable( achievementID, iNumSteps ) );
    }
    
    protected void setAchievementSteps( String achievementID, int iNumSteps )
    {
    	class SetAchievementStepsRunnable implements Runnable
	    {
	        private String 	mAchievementID;
	        private int		mNumSteps;
	        public SetAchievementStepsRunnable( String achievementID, int iNumSteps )
	        { 
	        	mAchievementID 	= achievementID;
	        	mNumSteps		= iNumSteps;
	        }
	 
	        @Override
	        public void run() 
	        {
	        	getGamesClient().setAchievementSteps( mAchievementID, mNumSteps );               
	        }	        
	    }
    
    	mGameHandler.post( new SetAchievementStepsRunnable( achievementID, iNumSteps ) );
    }
}

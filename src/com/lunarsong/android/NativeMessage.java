package com.lunarsong.android;

public class NativeMessage
{
	// Events
	public enum NativeEventType
	{
		ApplicationShutdown( 1001 ),	// Called on shutdown
		
		ApplicationPaused( 1002 ),		// Called from onPause callback
		ApplicationResumed( 1003 ),		// Called from onResume callback
				
		WindowVisible( 1004 ),			// Called when the window is visible
		WindowHidden( 1005 ),			// Called when the window is hidden
				
		SurfaceCreated( 1006 ),			// Called from surfaceCreated callback
		SurfaceDestroyed( 1007 ),		// Called from surfaceDestroyed callback
		SurfaceResized( 1008 );			// Called from surfaceChanged callback
				
		private final int mID;
		NativeEventType( int iID )
		{
			this.mID = iID;
		}
				
		public int getValue()
		{
			return this.mID;
		}
	}
	
	// Messages from Native
	public static final int NATIVE_QUIT = 1001;
	public static final int NATIVE_KEYBOARD_REQUEST_SHOW = 2001;
	public static final int NATIVE_KEYBOARD_REQUEST_HIDE = 2002;
	
	/***************************************************************/
	/*************** Google Play Services Messages *****************/
	/***************************************************************/
	
	// Leaderboards
	public static final int NATIVE_PLAYSERVICES_LEADERBOARD_SHOW			 	= 8001;
	public static final int NATIVE_PLAYSERVICES_LEADERBOARD_SCORE_SUBMIT	 	= 8002;
	
	// Achievements
	public static final int NATIVE_PLAYSERVICES_ACHIEVEMENTS_SHOW		 		= 8011;
	public static final int NATIVE_PLAYSERVICES_ACHIEVEMENTS_UNLOCK		 		= 8012;
	public static final int NATIVE_PLAYSERVICES_ACHIEVEMENTS_INCREMENT	 		= 8013;
	
	
	/**
	 * @param eType
	 */
	public NativeMessage( NativeEventType eType )
	{
		mType = eType;
		mID	  = eType.getValue();
	}
	
	public NativeEventType mType;
	public int mID;
}
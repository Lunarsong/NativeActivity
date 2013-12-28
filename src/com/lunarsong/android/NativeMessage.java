package com.lunarsong.android;

import android.view.Surface;

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
	public Surface mSurface;
}
package com.lunarsong.android;

import com.lunarsong.android.NativeSurfaceView.NativeThread;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.inputmethod.InputMethodManager;
import android.content.Context;

public class NativeGameActivity extends BaseGameActivity 
{
	NativeSurfaceView mNativeSurfaceView;
	private Handler mHandler;
	
    @Override
    protected void onCreate( Bundle savedInstanceState ) 
    {
        super.onCreate( savedInstanceState );
        
        // Create handler
 		mHandler = new Handler( Looper.getMainLooper() )
 		{
 			@Override
 	        public void handleMessage( Message inputMessage ) 
 			{
 				switch ( inputMessage.what )
 				{
 					case NativeMessage.NATIVE_QUIT:
 					{
 						//Log.v( "NativeActivity", "[NativeActivity]: Calling finish" );
 						
 						finish();
 					} break;
 					
 					case NativeMessage.NATIVE_KEYBOARD_REQUEST_SHOW:
 					{
 						//Log.v("NativeActivity", "NATIVE_KEYBOARD_REQUEST_SHOW" );
 						
 						if ( mNativeSurfaceView.requestFocus() ) 
 				    	{
 				            InputMethodManager imm = (InputMethodManager)getSystemService( Context.INPUT_METHOD_SERVICE );
 				            imm.showSoftInput( mNativeSurfaceView, InputMethodManager.SHOW_IMPLICIT );
 				           //beginUserInitiatedSignIn();
 				        }

 					} break;
 					
 					case NativeMessage.NATIVE_KEYBOARD_REQUEST_HIDE:
 					{
 						//Log.v("NativeActivity", "NATIVE_KEYBOARD_REQUEST_HIDE" );

 						InputMethodManager imm = (InputMethodManager)getSystemService( Context.INPUT_METHOD_SERVICE );
 				        imm.hideSoftInputFromWindow( mNativeSurfaceView.getWindowToken(), 0 );
 				       //startActivityForResult( getGamesClient().getAchievementsIntent(), 0);
 				        //getGamesClient().submitScore( "CgkIp8rf-fkTEAIQCA", 500 );
 				       //startActivityForResult(getGamesClient().getLeaderboardIntent( "CgkIp8rf-fkTEAIQCA" ), 1);
 					} break;
 				
 					default:
 					{
 						super.handleMessage( inputMessage );
 					}
 				}
 			}
 		};
        
        // Create the native surface view
        mNativeSurfaceView = new NativeSurfaceView( this, mHandler );
        mNativeSurfaceView.setFocusable(true);
        mNativeSurfaceView.setFocusableInTouchMode(true);
        
        setContentView( mNativeSurfaceView );
        getGamesClient().setViewForPopups( mNativeSurfaceView );
    }
    
    @Override protected void onPause()
    {
    	// Handle onPause();
    	mNativeSurfaceView.onPause();
    	
    	// Call super
    	super.onPause();
    }
    
    @Override protected void onResume()
    {
    	// Call super
    	super.onResume();
    	
    	// Handle onResume();
    	mNativeSurfaceView.onResume();
    }
    
    @Override protected void onDestroy()
    {
    	// Handle onResume();
    	mNativeSurfaceView.onDestroy();
    	
    	// Call super
    	super.onDestroy();
    }
    
    @Override public void onLowMemory()
    {
    	mNativeSurfaceView.queueEvent( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mNativeSurfaceView.nativeOnLowMemory();
            }
        });
    	
    	super.onLowMemory();
    }

	@Override
	public void onSignInFailed() 
	{
		mNativeSurfaceView.queueEvent( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mNativeSurfaceView.nativeOnSignInFailed();
            }
        });		
	}
	
	@Override
	public void onSignInSucceeded() 
	{
		final String accountName = "disabled";//getGamesClient().getCurrentAccountName();
		mNativeSurfaceView.queueEvent( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mNativeSurfaceView.nativeOnSignInSucceeded( accountName );
            }
        });
	}
    
}
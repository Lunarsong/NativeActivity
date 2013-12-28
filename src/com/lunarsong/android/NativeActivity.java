package com.lunarsong.android;

import android.os.Bundle;
import android.app.Activity;

public class NativeActivity extends Activity 
{
	NativeSurfaceView mNativeSurfaceView;
	
    @Override
    protected void onCreate( Bundle savedInstanceState ) 
    {
        super.onCreate( savedInstanceState );
        
        // Create the native surface view
        mNativeSurfaceView = new NativeSurfaceView( getApplication() );
        mNativeSurfaceView.setFocusable(true);
        mNativeSurfaceView.setFocusableInTouchMode(true);
        
        setContentView( mNativeSurfaceView );
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
}

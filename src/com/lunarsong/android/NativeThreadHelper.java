package com.lunarsong.android;

public class NativeThreadHelper 
{
	NativeGameActivity mActivity;
	
	public NativeThreadHelper( NativeGameActivity activity )
	{
		mActivity = activity;
	}
	
	public void runOnUIThread( Runnable runnable )
	{
		mActivity.getHandler().post( runnable );
	}
	
	public void runOnNativeThread( Runnable runnable )
	{
		mActivity.mNativeSurfaceView.queueEvent( runnable );
	}
}

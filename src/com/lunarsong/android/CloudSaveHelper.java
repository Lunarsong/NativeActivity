package com.lunarsong.android;

import com.google.android.gms.appstate.AppStateClient;
import com.google.android.gms.appstate.OnStateLoadedListener;

/**
 * @author Shanee
 * This is a helper class to handle Google's AppState for Cloud Save
 */
public class CloudSaveHelper extends NativeThreadHelper
{
	/**
	 * @author Shanee
	 * This class takes a pointer to a listener from C++ and implementes the AppState call back.
	 * Once the callbacks are called it passes back to C++ with the pointer so the waiting
	 * C++ Interface can continue its work 
	 */
	class CloudStateListener extends NativeThreadHelper implements
	OnStateLoadedListener
	{
		Object mListener;
		
		/**
		 * @param listener - C++ pointer to an interface to resolve the callback
		 * @param activity - Required by parent class to access Native thread.
		 */
		public CloudStateListener( Object listener, NativeGameActivity activity ) 
		{
			super( activity );
			
			mListener = listener;
		}

		@Override
	    public void onStateConflict( final int iStateKey, final String resolvedVersion, final byte[] localData,
	            final byte[] serverData )
		{		
			runOnNativeThread( new Runnable() 
	        {
	            @Override
	            public void run() 
	            {
	            	nativeOnStateConflict( mListener, iStateKey, resolvedVersion, localData, serverData );
	            }
	        });
	    }

		@Override
	    public void onStateLoaded( final int iStatusCode, final int iStateKey, final byte[] data ) 
		{
			runOnNativeThread( new Runnable() 
	        {
	            @Override
	            public void run() 
	            {
	            	nativeOnStateLoaded( mListener, iStatusCode, iStateKey, data );
	            }
	        });
		}
	}
	
	public CloudSaveHelper( NativeGameActivity activity ) 
	{
		super( activity );
	}
	
	void updateState( final int iStateKey, final byte[] pData )
	{
		runOnUIThread( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mActivity.getAppStateClient().updateState( iStateKey, pData );
            }
        });		
	}
	
	void updateStateImmediate( final Object pListener, final int iStateKey, final byte[] pData )
	{
		runOnUIThread( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mActivity.getAppStateClient().updateStateImmediate( new CloudStateListener( pListener, mActivity ), iStateKey, pData );
            }
        });
	}
	
	void loadState( final Object pListener, final int iStateKey )
	{
		runOnUIThread( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mActivity.getAppStateClient().loadState( new CloudStateListener( pListener, mActivity ), iStateKey );
            }
        });		
	}
	
	void resolveState( final Object pListener, final int iStateKey, final String resolvedVersion, final byte[] resolvedData )
	{
		runOnUIThread( new Runnable() 
        {
            @Override
            public void run() 
            {
            	mActivity.getAppStateClient().resolveState( new CloudStateListener( pListener, mActivity ), iStateKey, resolvedVersion, resolvedData );
            }
        });
	}
	
	private native void nativeOnStateConflict( final Object pListener, final int iStateKey, String versionId, final byte[] localData,
            final byte[] serverData );
	private native void nativeOnStateLoaded( final Object pListener, final int iStatusCode, final int iStateKey, final byte[] data );
}

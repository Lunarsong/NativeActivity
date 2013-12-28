#pragma once

/*
#define ApplicationShutdown 	 1001		// Called on shutdown

#define ApplicationPaused 		 1002		// Called from onPause callback
#define ApplicationResumed 		 1003		// Called from onResume callback

#define WindowAttached 			 1004		// Called from onAttachedToWindow callback
#define WindowDetached 			 1005		// Called from onDetachedFromWindow callback

#define SurfaceCreated 			 1006		// Called from surfaceCreated callback
#define SurfaceDestroyed 		 1007		// Called from surfaceDestroyed callback
#define SurfaceResized 			 1008		// Called from surfaceChanged callback
*/

enum AndroidMessageType
{
	ApplicationShutdown 	= 1001,		// Called on shutdown

	ApplicationPaused 		= 1002,		// Called from onPause callback
	ApplicationResumed 		= 1003,		// Called from onResume callback

	WindowVisible 			= 1004,		// Called when the window is visible
	WindowHidden 			= 1005,		// Called when the window is hidden

	SurfaceCreated 			= 1006,		// Called from surfaceCreated callback
	SurfaceDestroyed 		= 1007,		// Called from surfaceDestroyed callback
	SurfaceResized 			= 1008		// Called from surfaceChanged callback
};

struct AndroidMessage
{
	int iMessageID;
};

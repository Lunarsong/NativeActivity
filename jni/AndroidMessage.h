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
	AndroidMessage_ApplicationShutdown 		= 1001,		// Called on shutdown

	AndroidMessage_ApplicationPaused 		= 1002,		// Called from onPause callback
	AndroidMessage_ApplicationResumed 		= 1003,		// Called from onResume callback

	AndroidMessage_WindowVisible 			= 1004,		// Called when the window is visible
	AndroidMessage_WindowHidden 			= 1005,		// Called when the window is hidden

	AndroidMessage_SurfaceCreated 			= 1006,		// Called from surfaceCreated callback
	AndroidMessage_SurfaceDestroyed 		= 1007,		// Called from surfaceDestroyed callback
	AndroidMessage_SurfaceChanged 			= 1008,		// Called from surfaceChanged callback

	// Input
	AndroidMessage_OnTouch					= 1101,		// Called when the user touched the screen
	AndroidMessage_OnKey					= 1102,		// Called when the user pressed a key


	AndroidMessage_Undefined
};

/*************************************/
/*       AndroidMessage event		 */
/*************************************/

struct AndroidMessage
{
	int iMessageID;
	void* pData;

	AndroidMessage()
	{
		iMessageID 	= -1;
		pData		= 0;
	}
};

/*************************************/
/*       SurfaceChanged event		 */
/*************************************/
struct AndroidSurfaceChanged
{
	int iFormat;
	int iWidth;
	int iHeight;
};

/*************************************/
/*        AndroidTouch event		 */
/*************************************/
struct AndroidTouch
{
	enum TouchAction
	{
		Action_Down 			= 0,
		Action_Up				= 1,
		Action_Move				= 2,
		Action_Cancel			= 3,

		Action_Outside			= 4,

		Action_SecondaryDown	= 5,
		Action_SecondaryUp		= 6,

		TouchActionUndefined
	};

	int			iPointerID;
	int			iAction;		// = TouchAction
	float		fPosX;			// Left = 0.0f
	float		fPosY;			// Top = 0.0f
};

/*************************************/
/*          AndroidKey event		 */
/*************************************/
struct AndroidKey
{
	int iKeyCode;
	wchar_t iUnicodeChar;
};

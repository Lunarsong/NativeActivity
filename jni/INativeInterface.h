#pragma once

class INativeInterface
{
public:
	// Surface
	virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight ) = 0;
	virtual void OnSurfaceCreated( jobject pSurface ) = 0;
	virtual void OnSurfaceDestroyed() = 0;

	// Application state
	virtual void OnApplicationPaused() 	= 0;
	virtual void OnApplicationResumed() 	= 0;

	// Window state
	virtual void OnWindowHidden() 	= 0;
	virtual void OnWindowShown()	= 0;

	// Input
	virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction ) = 0;
	virtual void OnKeyUp( int iKeyCode, int iUnicodeChar ) = 0;

	virtual ~INativeInterface() { }
};

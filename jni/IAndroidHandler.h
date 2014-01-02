#pragma once

class IAndroidHandler
{
public:
	// Application
	virtual void OnShutdown() = 0;

	// Surface
	virtual void OnSurfaceCreated() = 0;
	virtual void OnSurfaceChanged( int iPixelFormat, int iWidth, int iHeight ) = 0;
	virtual void OnSurfaceDestroyed() = 0;

	// States
	virtual void OnPause() = 0;
	virtual void OnResume() = 0;

	virtual void OnVisible() = 0;
	virtual void OnHidden() = 0;

	virtual void OnLowMemory() = 0;

	// Input
	virtual void OnKey( int iKeyCode, wchar_t iUnicodeChar ) = 0;
	virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction ) = 0;

	virtual ~IAndroidHandler() { }
};

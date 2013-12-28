#pragma once

class INativeInterface
{
public:
	// Surface
	virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight ) = 0;

	// Input
	virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction ) = 0;
	virtual void OnKeyUp( int iKeyCode, int iUnicodeChar ) = 0;


	virtual ~INativeInterface() { }
};

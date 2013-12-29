#include "Android.h"
#include "AndroidLog.h"

NativeActivity Android::s_NativeActivity;

void Android::PollEvents()
{
	s_NativeActivity.PollEvents();
}

void Android::SetEventCallback( MessageCallbackFunction pCallback )
{
	s_NativeActivity.SetEventCallback( pCallback );
}

void Android::SetJNI( JNIEnv* pEnv, jobject pObj, INativeInterface** pInterface )
{
	LOGV( "[Android]: Setting JNI Environment." );
	s_NativeActivity.SetJNI( pEnv, pObj, pInterface );
}

ANativeWindow* Android::GetWindow()
{
	return s_NativeActivity.GetWindow();
}

bool Android::IsWindowVisible()
{
	return s_NativeActivity.IsVisible();
}

void Android::ShowKeyboard()
{
	s_NativeActivity.ShowKeyboard();
}

void Android::HideKeyboard()
{
	s_NativeActivity.HideKeyboard();
}

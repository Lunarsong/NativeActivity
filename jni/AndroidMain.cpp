#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>

#include "AndroidLog.h"
#include "INativeInterface.h"

extern "C"
{
    JNIEXPORT void JNICALL nativeMain( JNIEnv* pEnv, jobject pObj, jstring strApplicationName );
    JNIEXPORT void JNICALL nativeOnTouch( JNIEnv* env, jobject obj, int iPointerID, float fPosX, float fPosY, int iAction );
    JNIEXPORT void JNICALL nativeOnKeyUp( JNIEnv* env, jobject obj, int iKeyCode, int iUnicodeChar );
    JNIEXPORT void JNICALL nativeOnSurfaceChanged( JNIEnv* env, jobject obj, int iFormat, int iWidth, int iHeight );

};

static const JNINativeMethod g_NativeMethods[] =
{
    { "nativeMain", "(Ljava/lang/String;)V", (void*)nativeMain },
    { "nativeOnTouch", "(IFFI)V", (void*)nativeOnTouch },
    { "nativeOnKeyUp", "(II)V", (void*)nativeOnKeyUp },
    { "nativeOnSurfaceChanged", "(III)V", (void*)nativeOnSurfaceChanged },
};

#define NELEM( x ) ( (int) ( sizeof(x) / sizeof( (x) [0] ) ) )
jint JNI_OnLoad( JavaVM* pJavaVM, void* pReserved )
{
    JNIEnv* pEnv;
    if ( pJavaVM->GetEnv(reinterpret_cast<void**>( &pEnv ), JNI_VERSION_1_6) != JNI_OK )
    {
        return -1;
    }

    // Get jclass with pEnv->FindClass.
    // Register methods with pEnv->RegisterNatives.
    jclass javaLibClass = pEnv->FindClass( "com/lunarsong/android/NativeSurfaceView" );
    pEnv->RegisterNatives( javaLibClass, g_NativeMethods, NELEM( g_NativeMethods ) );

    LOGV( "NativeActivity C++ successfully loaded." );

    return JNI_VERSION_1_6;
}

INativeInterface* s_pNativeInterface = NULL;
JNIEXPORT void JNICALL nativeMain( JNIEnv* pEnv, jobject pObj, jstring strApplicationName )
{
	// Application Name
	const char* pApplicationName = pEnv->GetStringUTFChars( strApplicationName, NULL );
	char strLibName[ 128 ];
	sprintf( strLibName, "lib%s.so", pApplicationName );
	LOGV( "[Native]: Loading dynamic library: %s.", strLibName );

	pEnv->ReleaseStringUTFChars( strApplicationName, pApplicationName );

	// Error message
	const char* pErrorString = NULL;

	// Library functions
	void (*android_main)(void);
	void (*init_native_activity)( JNIEnv*, jobject, INativeInterface** );

	// Load library
	void* pLibraryHandle = dlopen( strLibName, RTLD_NOW | RTLD_GLOBAL );
	if ( !pLibraryHandle )
	{
		LOGE( "Could not load library" );
		throw "Error";
	}

	// Clear existing errors
	dlerror();

	// Retrieve android_main
	*(void **) (&android_main) = dlsym( pLibraryHandle, "android_main" );
	if ( ( pErrorString = dlerror() ) != NULL )
	{
		LOGE( "Could not find android_main %s", pErrorString );

		throw "Error";
	}

	// Retrieve init_native_activity
	*(void **) (&init_native_activity) = dlsym( pLibraryHandle, "init_native_activity" );
	if ( ( pErrorString = dlerror() ) != NULL )
	{
		LOGE( "Could not find init_native_activity %s", pErrorString );

		throw "Error";
	}

	// Init native activity
	init_native_activity( pEnv, pObj, &s_pNativeInterface );

	// Call user defined main
	(*android_main)();

	// Release the nativve interface
	delete s_pNativeInterface;
	s_pNativeInterface = NULL;

	dlclose( pLibraryHandle );
}

/**********************************************************************************/
/*                                     OnTouch                                    */
/**********************************************************************************/
JNIEXPORT void JNICALL nativeOnTouch( JNIEnv* env, jobject obj, int iPointerID, float fPosX, float fPosY, int iAction )
{
	if ( s_pNativeInterface )
	{
		s_pNativeInterface->OnTouch( iPointerID, fPosX, fPosY, iAction );
	}
}

JNIEXPORT void JNICALL nativeOnKeyUp( JNIEnv* env, jobject obj, int iKeyCode, int iUnicodeChar )
{
	if ( s_pNativeInterface )
	{
		s_pNativeInterface->OnKeyUp( iKeyCode, iUnicodeChar );
	}
}

JNIEXPORT void JNICALL nativeOnSurfaceChanged( JNIEnv* env, jobject obj, int iFormat, int iWidth, int iHeight )
{
	if ( s_pNativeInterface )
	{
		s_pNativeInterface->OnSurfaceChanged( iFormat, iWidth, iHeight );
	}
}

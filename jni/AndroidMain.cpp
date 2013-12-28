#include "AndroidLog.h"
#include <dlfcn.h>
#include <unistd.h>

extern "C"
{
    JNIEXPORT void JNICALL nativeMain( JNIEnv* pEnv, jobject pObj );
};

static const JNINativeMethod g_NativeMethods[] =
{
    { "nativeMain", "()V", (void*)nativeMain },
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

JNIEXPORT void JNICALL nativeMain( JNIEnv* pEnv, jobject pObj )
{
	// Error message
	const char* pErrorString = NULL;

	// Library functions
	void (*android_main)(void);
	void (*init_native_activity)( JNIEnv*, jobject );

	// Load library
	void* pLibraryHandle = dlopen( "libNativeExample.so", RTLD_NOW | RTLD_GLOBAL );
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
	init_native_activity( pEnv, pObj );

	// Call user defined main
	(*android_main)();

	dlclose( pLibraryHandle );
}

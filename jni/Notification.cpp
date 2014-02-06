/*
 * Notification.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#include "Notification.h"
#include <Android.h>
#include <AndroidLog.h>

namespace Android
{

	JNIEnv* Notification::s_pEnv						= NULL;

	jclass Notification::s_hClass = NULL;

	jmethodID Notification::s_hConstructorMethod		= NULL;

	jmethodID Notification::s_hSetAutoCancelMethod 		= NULL;
	jmethodID Notification::s_hSetContentTitleMethod 	= NULL;
	jmethodID Notification::s_hSetContentTextMethod 	= NULL;
	jmethodID Notification::s_hSetContentInfoMethod 	= NULL;
	jmethodID Notification::s_hSetSubTextMethod 		= NULL;

	jmethodID Notification::s_hSetDefaultsMethod 		= NULL;
	jmethodID Notification::s_hSetLightsMethod 			= NULL;
	jmethodID Notification::s_hSetNumberMethod 			= NULL;
	jmethodID Notification::s_hSetOngoingMethod 		= NULL;
	jmethodID Notification::s_hSetOnlyAlertOnceMethod 	= NULL;
	jmethodID Notification::s_hSetPriorityMethod 		= NULL;
	jmethodID Notification::s_hSetProgressMethod 		= NULL;
	jmethodID Notification::s_hSetWhenMethod 			= NULL;
	jmethodID Notification::s_hSetSmallIconMethod		= NULL;
	//jmethodID Notification::s_hSetLargeIconMethod		= NULL;

	jmethodID Notification::s_hBuildMethod 				= NULL;

	void Notification::InitJNI()
	{
		s_pEnv = Android::GetJNIEnv();
		s_hClass = (jclass)s_pEnv->NewGlobalRef( (jobject)Android::GetClassLoader().FindClass( "android.support.v4.app.NotificationCompat$Builder" ) );

		s_hConstructorMethod		= s_pEnv->GetMethodID( s_hClass, "<init>", "(Landroid/content/Context;)V" );

		s_hSetAutoCancelMethod 		= s_pEnv->GetMethodID( s_hClass, "setAutoCancel", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetContentTitleMethod 	= s_pEnv->GetMethodID( s_hClass, "setContentTitle", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetContentTextMethod 	= s_pEnv->GetMethodID( s_hClass, "setContentText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetContentInfoMethod 	= s_pEnv->GetMethodID( s_hClass, "setContentInfo", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetSubTextMethod 		= s_pEnv->GetMethodID( s_hClass, "setSubText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;" );

		s_hSetDefaultsMethod 		= s_pEnv->GetMethodID( s_hClass, "setDefaults", "(I)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetLightsMethod 			= s_pEnv->GetMethodID( s_hClass, "setLights", "(III)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetNumberMethod 			= s_pEnv->GetMethodID( s_hClass, "setNumber", "(I)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetOngoingMethod 		= s_pEnv->GetMethodID( s_hClass, "setOngoing", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetOnlyAlertOnceMethod 	= s_pEnv->GetMethodID( s_hClass, "setOnlyAlertOnce", "(Z)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetPriorityMethod 		= s_pEnv->GetMethodID( s_hClass, "setPriority", "(I)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetProgressMethod 		= s_pEnv->GetMethodID( s_hClass, "setProgress", "(IIZ)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetWhenMethod 			= s_pEnv->GetMethodID( s_hClass, "setWhen", "(J)Landroid/support/v4/app/NotificationCompat$Builder;" );
		s_hSetSmallIconMethod		= s_pEnv->GetMethodID( s_hClass, "setSmallIcon", "(I)Landroid/support/v4/app/NotificationCompat$Builder;" );

		s_hBuildMethod	 			= s_pEnv->GetMethodID( s_hClass, "build", "()Landroid/app/Notification;" );
	}

	Notification::Notification()
	{
		if ( !s_hClass )
		{
			InitJNI();
		}

		m_pNotificationBuilder = s_pEnv->NewObject( s_hClass, s_hConstructorMethod, Android::GetJNIActivity() );
		if ( m_pNotificationBuilder != NULL )
		{
			m_pNotificationBuilder = s_pEnv->NewGlobalRef( m_pNotificationBuilder );
		}
	}

	Notification::~Notification()
	{
		if ( m_pNotificationBuilder )
		{
			s_pEnv->DeleteGlobalRef( m_pNotificationBuilder );
		}
	}

	Notification& Notification::SetAutoCancel( bool bAutoCancel )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetAutoCancelMethod, bAutoCancel );

		return *this;
	}

	Notification& Notification::SetContentTitle( const char* pTitle )
	{
		jstring string = s_pEnv->NewStringUTF( pTitle );
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetContentTitleMethod, string );
		s_pEnv->DeleteLocalRef( string );

		return *this;
	}

	Notification& Notification::SetContentText( const char* pText )
	{
		jstring string = s_pEnv->NewStringUTF( pText );
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetContentTextMethod, string );
		s_pEnv->DeleteLocalRef( string );

		return *this;
	}

	Notification& Notification::SetContentInfo( const char* pInfo )
	{
		jstring string = s_pEnv->NewStringUTF( pInfo );
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetContentInfoMethod, string );
		s_pEnv->DeleteLocalRef( string );

		return *this;
	}

	Notification& Notification::SetSubText( const char* pSubText )
	{
		jstring string = s_pEnv->NewStringUTF( pSubText );
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetSubTextMethod, string );
		s_pEnv->DeleteLocalRef( string );

		return *this;
	}

	Notification& Notification::SetDefaults( int iDefaults )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetDefaultsMethod, iDefaults );

		return *this;
	}

	Notification& Notification::SetLights( int iARGB, int iOnMS, int iOffMS )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetLightsMethod, iARGB, iOnMS, iOffMS );

		return *this;
	}

	Notification& Notification::SetNumber( int iNumber )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetNumberMethod, iNumber );

		return *this;
	}

	Notification& Notification::SetOngoing( bool bOngoing )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetOngoingMethod, bOngoing );

		return *this;
	}

	Notification& Notification::SetOnlyAlertOnce( bool bOnlyAlertOnce )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetOnlyAlertOnceMethod, bOnlyAlertOnce );

		return *this;
	}

	Notification& Notification::SetPriority( int iPriority )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetPriorityMethod, iPriority );

		return *this;
	}

	Notification& Notification::SetProgress( int iMax, int iProgress, bool bIndeterminate )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetProgressMethod, iMax, iProgress, bIndeterminate );

		return *this;
	}

	Notification& Notification::SetWhen( long lWhen )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetWhenMethod, lWhen );

		return *this;
	}

	Notification& Notification::SetSmallIcon( int iIcon )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetSmallIconMethod, iIcon );

		return *this;
	}

	/*Notification& Notification::SetLargeIcon( int iIcon )
	{
		s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hSetLargeIconMethod, iIcon );

		return *this;
	}*/
	jobject Notification::Build() const
	{
		return s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hBuildMethod );
	}

	void Notification::Dispatch( int iNotificationID )
	{
		LOGV( "Dispatching notification" );
		jobject pNotification = s_pEnv->CallObjectMethod( m_pNotificationBuilder, s_hBuildMethod );

		jobject pNotificationService = Android::GetNativeActivity().GetSystemService( "notification" );
		jclass hNotificationClass = s_pEnv->GetObjectClass( pNotificationService );
		jmethodID hNotify = s_pEnv->GetMethodID( hNotificationClass, "notify", "(ILandroid/app/Notification;)V" );

		s_pEnv->CallVoidMethod( pNotificationService, hNotify, iNotificationID, pNotification );
	}

} /* namespace Android */

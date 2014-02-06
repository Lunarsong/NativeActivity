/*
 * NotificationManager.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#include "NotificationManager.h"
#include <Android.h>

namespace Android
{

	NotificationManager::NotificationManager()
	{
		m_pEnv 				= NULL;

		m_hCancelMethod 	= NULL;
		m_hCancelTagMethod 	= NULL;
		m_hCancelAllMethod 	= NULL;
		m_hNotifyMethod 	= NULL;
		m_hNotifyTagMethod	= NULL;
	}

	NotificationManager::~NotificationManager()
	{

	}

	void NotificationManager::Cancel( int iNotificationID )
	{
		jobject pObject = GetObject();

		m_pEnv->CallVoidMethod( pObject, m_hCancelMethod, iNotificationID );
	}

	void NotificationManager::Cancel( const char* pTag, int iNotificationID )
	{
		jobject pObject = GetObject();

		jstring string = m_pEnv->NewStringUTF( pTag );
		m_pEnv->CallVoidMethod( pObject, m_hCancelTagMethod, string, iNotificationID );
		m_pEnv->DeleteLocalRef( string );
	}

	void NotificationManager::CancelAll()
	{
		jobject pObject = GetObject();

		m_pEnv->CallVoidMethod( pObject, m_hCancelAllMethod );
	}

	void NotificationManager::Notify( int iNotificationID, const Notification& notification )
	{
		jobject pObject = GetObject();

		m_pEnv->CallVoidMethod( pObject, m_hNotifyMethod, iNotificationID, notification.Build() );
	}

	void NotificationManager::Notify( const char* pTag, int iNotificationID, const Notification& notification )
	{
		jobject pObject = GetObject();

		jstring string = m_pEnv->NewStringUTF( pTag );
		m_pEnv->CallVoidMethod( pObject, m_hNotifyTagMethod, string, iNotificationID, notification.Build() );
		m_pEnv->DeleteLocalRef( string );
	}

	void NotificationManager::Init()
	{
		m_pEnv = Android::GetJNIEnv();
		jobject pObject = GetObject();

		jclass hNotificationClass = m_pEnv->GetObjectClass( pObject );

		m_hCancelMethod 	= m_pEnv->GetMethodID( hNotificationClass, "cancel", "(I)V" );
		m_hCancelTagMethod 	= m_pEnv->GetMethodID( hNotificationClass, "cancel", "(Ljava/lang/String;I)V" );
		m_hCancelAllMethod 	= m_pEnv->GetMethodID( hNotificationClass, "cancelAll", "()V" );
		m_hNotifyMethod 	= m_pEnv->GetMethodID( hNotificationClass, "notify", "(ILandroid/app/Notification;)V" );
		m_hNotifyTagMethod	= m_pEnv->GetMethodID( hNotificationClass, "notify", "(Ljava/lang/String;ILandroid/app/Notification;)V" );
	}

	jobject NotificationManager::GetObject()
	{
		jobject pNotificationService = Android::GetNativeActivity().GetSystemService( "notification" );

		return pNotificationService;
	}

} /* namespace Android */

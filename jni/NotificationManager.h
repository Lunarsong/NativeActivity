/*
 * NotificationManager.h
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#ifndef NOTIFICATIONMANAGER_H_
#define NOTIFICATIONMANAGER_H_

#include "Notification.h"
#include <jni.h>

namespace Android
{
	class NotificationManager
	{
	public:
		NotificationManager();
		~NotificationManager();

		void Cancel( int iNotificationID );
		void Cancel( const char* pTag, int iNotificationID );
		void CancelAll();

		void Notify( int iNotificationID, const Notification& notification );
		void Notify( const char* pTag, int iNotificationID, const Notification& notification );

		void Init();

	private:
		JNIEnv* m_pEnv;

		jmethodID m_hCancelMethod;
		jmethodID m_hCancelTagMethod;
		jmethodID m_hCancelAllMethod;
		jmethodID m_hNotifyMethod;
		jmethodID m_hNotifyTagMethod;

		inline jobject GetObject();
	};

} /* namespace Android */
#endif /* NOTIFICATIONMANAGER_H_ */

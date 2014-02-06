/*
 * Notification.h
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <jni.h>

/*
 * http://developer.android.com/reference/android/support/v4/app/NotificationCompat.Builder.html
 */

namespace Android
{
	class Notification
	{
	public:
		Notification();
		virtual ~Notification();

		Notification& SetAutoCancel( bool bAutoCancel );
		Notification& SetContentTitle( const char* pTitle );
		Notification& SetContentText( const char* pText );
		Notification& SetContentInfo( const char* pInfo );
		Notification& SetSubText( const char* pSubText );
		Notification& SetDefaults( int iDefaults );
		enum Defaults
		{
			DEFAULT_SOUND 		= 0x00000001,
			DEFAULT_VIBRATE		= 0x00000002,
			DEFAULT_LIGHTS		= 0x00000004,
			DEFAULT_ALL			= 0xffffffff
		};

		Notification& SetLights( int iARGB, int iOnMS, int iOffMS );
		Notification& SetNumber( int iNumber );
		Notification& SetOngoing( bool bOngoing );
		Notification& SetOnlyAlertOnce( bool bOnlyAlertOnce );
		Notification& SetPriority( int iPriority );
		Notification& SetProgress( int iMax, int iProgress, bool bIndeterminate );
		Notification& SetWhen( long lWhen );

		Notification& SetSmallIcon( int iIcon );
		//Notification& SetLargeIcon( int iIcon );

		void Dispatch( int iNotificationID );
		jobject Build() const;

	private:
		jobject m_pNotificationBuilder;

		// JNI
		static void InitJNI();

		static JNIEnv* s_pEnv;

		// Class
		static jclass s_hClass;

		// Constructor
		static jmethodID s_hConstructorMethod;

		// Methods
		static jmethodID s_hSetAutoCancelMethod;
		static jmethodID s_hSetContentTitleMethod;
		static jmethodID s_hSetContentTextMethod;
		static jmethodID s_hSetContentInfoMethod;
		static jmethodID s_hSetSubTextMethod;
		static jmethodID s_hSetDefaultsMethod;
		static jmethodID s_hSetLightsMethod;
		static jmethodID s_hSetNumberMethod;
		static jmethodID s_hSetOngoingMethod;
		static jmethodID s_hSetOnlyAlertOnceMethod;
		static jmethodID s_hSetPriorityMethod;
		static jmethodID s_hSetProgressMethod;
		static jmethodID s_hSetWhenMethod;
		static jmethodID s_hSetSmallIconMethod;
		//static jmethodID s_hSetLargeIconMethod;

		static jmethodID s_hBuildMethod;
	};

} /* namespace Android */
#endif /* NOTIFICATION_H_ */

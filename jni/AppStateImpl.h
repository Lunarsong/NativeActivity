/*
 * AppStateImpl.h
 *
 *  Created on: Jan 31, 2014
 *      Author: Shanee
 */

#ifndef APPSTATEIMPL_H_
#define APPSTATEIMPL_H_

#include "IAppStateInterface.h"
#include <jni.h>

namespace Android
{
	class AppStateImpl : public IAppStateInterface
	{
	public:
		AppStateImpl( JNIEnv* pEnv );
		virtual ~AppStateImpl();

		void OnStateLoaded( const jobject pListener, const int iStatusCode, const int iStateKey, const jbyteArray data );
		void OnStateConflict( const jobject pListener, const int iStateKey, const jstring resolvedVersion, const jbyteArray localData, const jbyteArray serverData );

	private:
		JNIEnv* m_pEnv;
	};

} /* namespace Android */
#endif /* APPSTATEIMPL_H_ */

/*
 * IAppStateInterface.h
 *
 *  Created on: Jan 31, 2014
 *      Author: Shanee
 */

#ifndef IAPPSTATEINTERFACE_H_
#define IAPPSTATEINTERFACE_H_

#include <JNI.h>

namespace Android
{
	class IAppStateInterface
	{
	public:
		virtual void OnStateLoaded( const jobject pListener, const int iStatusCode, const int iStateKey, const jbyteArray data ) = 0;
		virtual void OnStateConflict( const jobject pListener, const int iStateKey, const jstring resolvedVersion, const jbyteArray localData, const jbyteArray serverData ) = 0;

		virtual ~IAppStateInterface() { }
	};

} /* namespace Android */
#endif /* IAPPSTATEINTERFACE_H_ */

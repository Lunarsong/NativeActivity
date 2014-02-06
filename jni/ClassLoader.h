/*
 * ClassLoader.h
 *
 *  Created on: Feb 6, 2014
 *      Author: Shanee
 */

#ifndef CLASSLOADER_H_
#define CLASSLOADER_H_

#include <jni.h>

namespace Android
{
	class ClassLoader
	{
	public:
		ClassLoader();
		~ClassLoader();

		jclass FindClass( const char* pClassName );

		void InitJNI( JNIEnv* pEnv, jclass hActivityClass, jobject pActivityObject );

	private:
		JNIEnv* m_pEnv;
		jclass 	m_hClass;
		jobject m_pObject;

		jmethodID	m_hFindClassMethod;

	};

} /* namespace Android */
#endif /* CLASSLOADER_H_ */

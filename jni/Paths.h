/*
 * Paths.h
 *
 *  Created on: Jan 14, 2014
 *      Author: Shanee
 */

#pragma once

namespace Android
{
	class Paths
	{
	public:
		~Paths();

		unsigned int Size();
		const char* operator[] ( unsigned int uiIndex ) const;

	private:
		unsigned int m_uiSize;
		char** m_pPaths;

		Paths( char** pPaths, unsigned int uiSize );

		friend class AssetManager;
	};

}

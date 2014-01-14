/*
 * Paths.cpp
 *
 *  Created on: Jan 14, 2014
 *      Author: Shanee
 */

#include "Paths.h"
#include <assert.h>

namespace Android
{
	Paths::Paths( char** pPaths, unsigned int uiSize )
	{
		m_uiSize = uiSize;
		m_pPaths = pPaths;
	}

	Paths::~Paths()
	{
		if ( m_pPaths )
		{
			for ( unsigned int i = 0; i < m_uiSize; ++i )
			{
				delete [] m_pPaths[ i ];
			}

			delete [] m_pPaths;
		}
	}

	unsigned int Paths::Size()
	{
		return m_uiSize;
	}

	const char* Paths::operator[] ( unsigned int uiIndex ) const
	{
		assert( uiIndex < m_uiSize );

		return m_pPaths[ uiIndex ];
	}
}

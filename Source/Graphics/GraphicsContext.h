/*
Copyright (C) 2001 StrmnNrmn

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef __DAEDALUS_GRAPHICSCONTEXT_H__
#define __DAEDALUS_GRAPHICSCONTEXT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Utility/Singleton.h"

class c32;

// This class basically provides an extra level of security for our
// multithreaded code. Threads can Grab the CGraphicsContext to prevent
// other threads from changing/releasing any of the pointers while it is
// running.

class CGraphicsContext : public CSingleton< CGraphicsContext >
{
public:
	virtual ~CGraphicsContext() {}

	enum ETargetSurface
	{
		TS_BACKBUFFER,
		TS_FRONTBUFFER,
	};

	virtual bool Initialise() = 0;

	virtual bool IsInitialised() const = 0;

#ifdef DAEDALUS_PSP
	virtual void SwitchToChosenDisplay() = 0;
	virtual void SwitchToLcdDisplay() = 0;
	virtual void StoreSaveScreenData() = 0;
#endif

	virtual void ClearAllSurfaces() = 0;
	virtual void ClearToBlack() = 0;
	virtual void ClearZBuffer() = 0;
	virtual void ClearColBuffer(const c32 & colour) = 0;
	virtual void ClearWithColour(u32 frame_buffer_col, u32 depth) = 0;

	virtual	void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void UpdateFrame( bool wait_for_vbl ) = 0;

	virtual void GetScreenSize(u32 * width, u32 * height) const = 0;
	virtual void SetDebugScreenTarget( ETargetSurface buffer ) = 0;

	virtual void ViewportType( u32 * d_width, u32 * d_height ) = 0;
	virtual void DumpNextScreen() = 0;
	virtual void DumpScreenShot() = 0;
};

#endif // __DAEDALUS_GRAPHICSCONTEXT_H__

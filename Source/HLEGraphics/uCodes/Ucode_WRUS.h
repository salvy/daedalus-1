/*
Copyright (C) 2009 StrmnNrmn

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

#ifndef HLEGRAPHICS_UCODES_UCODE_WRUS_H_
#define HLEGRAPHICS_UCODES_UCODE_WRUS_H_

//*****************************************************************************
// The previous way of calculating was based on the assumption that
// there was no "n" field. I didn't realise that the n/length fields shared the
// lower 16 bits (in a 7:9 split).
// u32 length    = (command.inst.cmd0)&0xFFFF;
// u32 num_verts = (length + 1) / 0x210;					// 528
// u32 v0_idx    = ((command.inst.cmd0>>16)&0xFF)/VertexStride;	// /5
//*****************************************************************************
void DLParser_GBI0_Vtx_WRUS( MicroCodeCommand command )
{
	auto addr {RDPSegAddr(command.inst.cmd1)};
	auto v0  {((command.inst.cmd0 >>16 ) & 0xff) / 5};
	auto n   {(command.inst.cmd0 >>9  ) & 0x7f};
	auto len {(command.inst.cmd0      ) & 0x1ff};
			#ifdef DAEDALUS_DEBUG_DISPLAYLIST
	DL_PF( "    Address[0x%08x] v0[%d] Num[%d] Len[0x%04x]", addr, v0, n, len );
#endif
#ifdef DAEDALUS_ENABLE_ASSERTS
	DAEDALUS_ASSERT( (v0 + n) < 32, "Warning, attempting to load into invalid vertex positions");
#endif
	gRenderer->SetNewVertexInfo( addr, v0, n );

#ifdef DAEDALUS_DEBUG_DISPLAYLIST
	gNumVertices += n;
	DLParser_DumpVtxInfo( addr, v0, n );
#endif

}

#endif // HLEGRAPHICS_UCODES_UCODE_WRUS_H_

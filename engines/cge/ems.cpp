/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This code is based on original Soltys source code
 * Copyright (c) 1994-1995 Janus B. Wisniewski and L.K. Avalon
 */

#include "cge/general.h"

namespace CGE {

#define EMS_INT     0x67
#define PAGE_MASK   0x3FFF
#define SIZ(n)      ((n) ? ((long)n) : (0x10000L))


enum EMM_FUN {
	GET_STATUS = 0x40, GET_FRAME, GET_SIZE,     OPEN_HANDLE,  MAP_PAGE,
	CLOSE_HANDLE,      GET_VER,   SAVE_CONTEXT, REST_CONTEXT, GET_PAGES = 0x4B,
	GET_HANDLES,       GET_INFO,  CONTROL
};


void *EMM::_frame = NULL;


EMM::EMM(long size): _han(-1), _top(0), _lim(0), _list(NULL) {
	/*
	    if (Test())
	    {
	      asm   mov ah,GET_FRAME    // get EMS frame segment
	      asm   int EMS_INT     // do it!
	      asm   or  ah,ah       // see status
	      asm   jnz xit     // abort on error
	      Frame = (void _seg *) _BX;    // save frame segment

	      if (size == 0)
	    {
	      asm   mov ah,GET_SIZE // get EMS memory size
	      asm   int EMS_INT     // do it!
	      asm   or  ah,ah       // see status
	      asm   jnz xit     // abort on error
	      asm   or  bx,bx       // test page count
	      asm   jz  xit     // abort if no free pages
	      // number of available pages in BX is ready to use by OPEN
	    }
	      else _BX = (uint16) ((size + PAGE_MASK) >> 14);
	      asm   mov ah,OPEN_HANDLE  // open EMM handle
	      asm   int EMS_INT     // do it!
	      asm   or  ah,ah       // see status
	      asm   jnz xit     // abort on error
	      Han = _DX;
	      Lim = _BX;
	      Lim <<= 14;
	      _DX = Han;
	      asm   mov ah,SAVE_CONTEXT // save mapping context
	      asm   int EMS_INT     // do it!
	    }
	  xit:
	*/
	warning("STUB: EMM:EMM");
}


EMM::~EMM(void) {
	/* FIXME
	  Release();
	  if (Han >= 0)
	    {
	      _DX = Han;
	      asm   mov ah,REST_CONTEXT
	      asm   int EMS_INT
	      asm   mov ah,CLOSE_HANDLE
	      asm   int EMS_INT
	    }
	*/
}


bool EMM::test() {
	/*
	  static char e[] = "EMMXXXX0";

	  asm   mov ax,0x3D40
	  asm   mov dx,offset e
	  asm   int 0x21
	  asm   jc  fail

	  asm   push    ax
	  asm   mov bx,ax
	  asm   mov ax,0x4407
	  asm   int 0x21

	  asm   pop bx
	  asm   push    ax
	  asm   mov ax,0x3E00
	  asm   int 0x21
	  asm   pop ax

	  asm   cmp al,0x00
	  asm   je  fail

	  success:
	  return TRUE;
	  fail:
	  return FALSE;
	*/
	warning("EMM::Test");
	return false;
}


EMS *EMM::alloc(uint16 siz) {
	/*
	  long size = SIZ(siz),
	       top = Top;

	  uint16 pgn = (uint16) (top >> 14),
	       cnt = (uint16) ((top + size + PAGE_MASK) >> 14) - pgn;

	  if (cnt > 4)
	    {
	      top = (top + PAGE_MASK) & 0xFFFFC000L;
	      pgn++;
	      cnt--;
	    }

	  if (size <= Lim - top)
	    {
	      EMS * e = new EMS, * f;

	      if (e)
	    {
	      Top = (e->Ptr = top) + (e->Siz = siz);
	      e->Emm = this;

	      if (List)
	        {
	          for (f = List; f->Nxt; f = f->Nxt);
	          return (f->Nxt = e);      // existing list: link to the end
	        }
	      else
	        {
	          return (List = e);        // empty list: link to the head
	        }
	    }
	    }
	  fail: return NULL;
	*/
	warning("STUB: EMM::alloc");
	return NULL;
}


void EMM::release() {
	while (_list) {
		EMS *e = _list;
		_list = e->_next;
		delete e;
	}
	_top = 0;
}


EMS::EMS(void) : _ptr(0), _size(0), _next(NULL) {
}


void *EMS::operator & () const {
	/*
	  uint16 pgn = (uint16) (Ptr >> 14),
	       off = (uint16) Ptr & PAGE_MASK,
	       cnt = (uint16) ((Ptr + SIZ(Siz) + PAGE_MASK) >> 14) - pgn,
	       cmd = MAP_PAGE << 8;

	  _DX = Emm->_han;       // take EMM handle
	  asm   dec cnt     // prapare for deferred checking
	  asm   or  dx,dx       // see if valid
	  asm   jns more        // negative handle = unavailable

	  fail: return NULL;

	  more:
	  asm   mov ax,cmd      // command + page frame index
	  asm   mov bx,pgn      // logical page number
	  asm   int EMS_INT     // do it!
	  asm   or  ah,ah       // check error code
	  asm   jnz fail        // exit on error
	  asm   inc cmd     // advance page frame index
	  asm   inc pgn     // advance logical page number
	  asm   cmp al,byte ptr cnt // all pages?
	  asm   jb  more

	  return (void *) (EMM::Frame + (void *) off);
	*/
	warning("STUB: EMS::operator &");
	return NULL;
}


uint16 EMS::size() {
	return _size;
}

} // End of namespace CGE

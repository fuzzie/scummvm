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
#include "cge/text.h"
#include "cge/talk.h"
#include "cge/vol.h"
#include "cge/bitmaps.h"
#include "cge/game.h"
#include "cge/snail.h"
#include "cge/cge_main.h"

namespace CGE {

TEXT *Text;
TALK *Talk = NULL;

TEXT::TEXT(CGEEngine *vm, const char *fname, int size) : _vm(vm) {
	Cache = new HAN[size];
	mergeExt(FileName, fname, SAY_EXT);
	if (!INI_FILE::exist(FileName))
		error("No talk (%s)\n", FileName);

	for (Size = 0; Size < size; Size++) {
		Cache[Size].Ref = 0;
		Cache[Size].Txt = NULL;
	}
}


TEXT::~TEXT() {
	Clear();
	delete[] Cache;
}


void TEXT::Clear(int from, int upto) {
	HAN *p, * q;
	for (p = Cache, q = p + Size; p < q; p++) {
		if (p->Ref && p->Ref >= from && p->Ref < upto) {
			p->Ref = 0;
			delete p->Txt;
			p->Txt = NULL;
		}
	}
}


int TEXT::Find(int ref) {
	HAN *p, * q;
	int i = 0;
	for (p = Cache, q = p + Size; p < q; p++) {
		if (p->Ref == ref)
			break;
		else
			++i;
	}
	return i;
}


void TEXT::Preload(int from, int upto) {
	INI_FILE tf = FileName;
	if (!tf._error) {
		HAN *CacheLim = Cache + Size;
		char line[LINE_MAX + 1];
		int n;

		while ((n = tf.read((uint8 *)line)) != 0) {
			char *s;
			int ref;

			if (line[n - 1] == '\n')
				line[-- n] = '\0';
			if ((s = strtok(line, " =,;/\t\n")) == NULL)
				continue;
			if (! IsDigit(*s))
				continue;
			ref = atoi(s);
			if (ref && ref >= from && ref < upto) {
				HAN *p;

				p = &Cache[Find(ref)];
				if (p < CacheLim) {
					delete[] p->Txt;
					p->Txt = NULL;
				} else
					p = &Cache[Find(0)];
				if (p >= CacheLim)
					break;
				s += strlen(s);
				if (s < line + n)
					++s;
				if ((p->Txt = new char[strlen(s) + 1]) == NULL)
					break;
				p->Ref = ref;
				strcpy(p->Txt, s);
			}
		}
	}
}


char *TEXT::Load(int idx, int ref) {
	INI_FILE tf = FileName;
	if (!tf._error) {
		HAN *p = &Cache[idx];
		char line[LINE_MAX + 1];
		int n;

		while ((n = tf.read((uint8 *)line)) != 0) {
			char *s;

			if (line[n - 1] == '\n')
				line[-- n] = '\0';
			if ((s = strtok(line, " =,;/\t\n")) == NULL)
				continue;
			if (! IsDigit(*s))
				continue;

			int r = atoi(s);
			if (r < ref)
				continue;
			if (r > ref)
				break;
			// (r == ref)
			s += strlen(s);
			if (s < line + n)
				++s;
			p->Ref = ref;
			if ((p->Txt = new char[strlen(s) + 1]) == NULL)
				return NULL;
			return strcpy(p->Txt, s);
		}
	}
	return NULL;
}


char *TEXT::getText(int ref) {
	int i;
	if ((i = Find(ref)) < Size)
		return Cache[i].Txt;

	if ((i = Find(0)) >= Size) {
		Clear(SYSTXT_MAX);            // clear non-system
		if ((i = Find(0)) >= Size) {
			Clear();              // clear all
			i = 0;
		}
	}
	return Load(i, ref);
}


void TEXT::Say(const char *txt, Sprite *spr) {
	KillText();
	Talk = new TALK(_vm, txt, ROUND);
	if (Talk) {
		bool east = spr->_flags._east;
		int x = (east) ? (spr->_x + spr->_w - 2) : (spr->_x + 2);
		int y = spr->_y + 2;
		Sprite *spike = new Sprite(_vm, SP);
		uint16 sw = spike->_w;

		if (east) {
			if (x + sw + TEXT_RD + 5 >= SCR_WID)
				east = false;
		} else {
			if (x <= 5 + TEXT_RD + sw)
				east = true;
		}
		x = (east) ? (spr->_x + spr->_w - 2) : (spr->_x + 2 - sw);
		if (spr->_ref == 1)
			x += ((east) ? -10 : 10); // Hero

		Talk->_flags._kill = true;
		Talk->_flags._bDel = true;
		Talk->setName(Text->getText(SAY_NAME));
		Talk->gotoxy(x - (Talk->_w - sw) / 2 - 3 + 6 * east, y - spike->_h - Talk->_h + 1);
		Talk->_z = 125;
		Talk->_ref = SAY_REF;

		spike->gotoxy(x, Talk->_y + Talk->_h - 1);
		spike->_z = 126;
		spike->_flags._slav = true;
		spike->_flags._kill = true;
		spike->setName(Text->getText(SAY_NAME));
		spike->step(east);
		spike->_ref = SAY_REF;

		Vga->ShowQ->Insert(Talk, Vga->ShowQ->Last());
		Vga->ShowQ->Insert(spike, Vga->ShowQ->Last());
	}
}

void CGEEngine::inf(const char *txt) {
	KillText();
	Talk = new TALK(this, txt, RECT);
	if (Talk) {
		Talk->_flags._kill = true;
		Talk->_flags._bDel = true;
		Talk->setName(Text->getText(INF_NAME));
		Talk->center();
		Talk->gotoxy(Talk->_x, Talk->_y - 20);
		Talk->_z = 126;
		Talk->_ref = INF_REF;
		Vga->ShowQ->Insert(Talk, Vga->ShowQ->Last());
	}
}


void SayTime(Sprite *spr) {
	/*
	  static char t[] = "00:00";
	  struct time ti;
	  gettime(&ti);
	  wtom(ti.ti_hour, t+0, 10, 2);
	  wtom(ti.ti_min,  t+3, 10, 2);
	  Say((*t == '0') ? (t+1) : t, spr);
	  */
	warning("STUB: SayTime");
}

void KillText(void) {
	if (Talk) {
		SNPOST_(SNKILL, -1, 0, Talk);
		Talk = NULL;
	}
}

} // End of namespace CGE

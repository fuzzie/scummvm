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

#include "onscreendialog.h"
#include "gui/gui-manager.h"
#include "common/rect.h"
#include "common/system.h"

namespace GUI {

bool OnScreenDialog::isVisible() const {
	return true;
}

enum {
	kStopCmd = 'PLAY'
};

void OnScreenDialog::reflowLayout() {
	GuiObject::reflowLayout();
}

void OnScreenDialog::releaseFocus() {
}

OnScreenDialog::OnScreenDialog(int x, int y, int w, int h) : Dialog(x, y, w, h) {
	GUI::PicButtonWidget *btn = new PicButtonWidget(this, "", "|>", kStopCmd);
	btn->useThemeTransparency(true);
	btn->resize(0,0,32,32);
	btn->setGfx(g_gui.theme()->getImageSurface(ThemeEngine::kImageStopbtn));
	text = new GUI::StaticTextWidget(this, "", "00:00:00");
	text->resize(40,5,50,30);
	uint32 lastTime = 0;
}

void OnScreenDialog::handleCommand(CommandSender *sender, uint32 cmd, uint32 data) {
	switch (cmd) {
	case kStopCmd:
		g_eventRec.togglePause();
		break;
	}
}

void OnScreenDialog::setReplayedTime(uint32 newTime) {
	uint32 delay = newTime - lastTime;
	if (newTime - lastTime > 1000) {
		uint32 seconds = newTime / 1000;
		text->setLabel(Common::String::format("%.2d:%.2d:%.2d", seconds / 3600 % 24, seconds / 60 % 60, seconds % 60));
		lastTime = newTime;
	}
}



}

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
 * $URL$
 * $Id$
 *
 */

#ifndef BACKENDS_PLUGINS_DYNAMICPLUGIN_H
#define BACKENDS_PLUGINS_DYNAMICPLUGIN_H

#include "base/plugins.h"


class DynamicPlugin : public Plugin {
protected:
	typedef int32 (*IntFunc)();
	typedef void (*VoidFunc)();
	typedef PluginObject *(*GetObjectFunc)();

	virtual VoidFunc findSymbol(const char *symbol) = 0;

public:
	virtual bool loadPlugin() {
 		// Get the type of the plugin
 		IntFunc typeFunc = (IntFunc)findSymbol("PLUGIN_getType");
 		if (!typeFunc) {
 			unloadPlugin();
 			return false;
 		}
 		_type = (PluginType)typeFunc();
 		if (_type >= PLUGIN_TYPE_MAX) {
 			unloadPlugin();
 			return false;
 		}

		// Get the plugin's instantiator object
		GetObjectFunc getObject = (GetObjectFunc)findSymbol("PLUGIN_getObject");
		if (!getObject) {
			unloadPlugin();
			return false;
		}

		// Get the plugin object
		_pluginObject = getObject();
		if (!_pluginObject) {
			unloadPlugin();
			return false;
		}

		return true;
	}

	virtual void unloadPlugin() {
		delete _pluginObject;
	}
};

#endif

/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include <iostream>
#include "OpenGLInterface.h"

extern "C"
{
	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new any_fw::SimpleItemFactory<any_fw::OpenGLInterface*>("OpenGLInterface"));
		return plugin;
	}
}

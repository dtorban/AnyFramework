/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include <iostream>
#include "GLFWInterface.h"

extern "C"
{
	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		/*   GLFWwindow* window;

		   if( !glfwInit() )
		      std::cout << "Error initializing GLFW" << std::endl;

		   window = glfwCreateWindow( 400, 400, "Boing (classic Amiga demo)", NULL, NULL );

		   while(true) {}

		   if (!window)
		   {
		       glfwTerminate();
		       //return NULL;
		}*/

		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new any_fw::SimpleItemFactory<any_fw::GLFWInterface*>("GLFWInterface"));
		return plugin;
	}
}

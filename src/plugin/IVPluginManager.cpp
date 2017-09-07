/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#if defined(WIN32)
#else
#include <dirent.h>
#endif

#include "IVPluginManager.h"
#include <iostream>
#include <fstream>
#include "utilities/FileHelpers.h"

namespace any_fw {

IVPluginManager::IVPluginManager() : factory(factories) {
	addAPI(&factories);
}

IVPluginManager::~IVPluginManager() {
	for (int f = 0; f < factories.size(); f++) {
		delete factories[f];
	}
}

void IVPluginManager::loadInstalledPlugins() {
	loadPlugins(std::string(INSTALLPATH) + "/plugins");
}

void IVPluginManager::loadPlugins(const std::string& pluginPath) {
	std::vector<std::string> pluginDirs = listDirectory(pluginPath, true);

	for (int f = 0; f < pluginDirs.size(); f++) {
		if (pluginDirs[f].find(".plugin") != std::string::npos) {
			if (loadedPlugins.find(pluginDirs[f]) == loadedPlugins.end()) {
				std::string pluginDir = pluginPath + "/" + pluginDirs[f];

				loadLibraries(pluginDir);

				loadedPlugins.insert(pluginDirs[f]);
			}
		}
	}
}

void IVPluginManager::loadLibraries(const std::string& pluginDir) {

	std::string dir = "/lib/";
	std::string debugPostFix = "_d";

#if defined(WIN32)
	dir = "/bin/";
	std::string ext = ".dll";
#elif defined(__APPLE__)
	std::string ext = ".dylib";
#else
	std::string ext = ".so";
#endif

#ifdef SpatializeProject_DEBUG
	int debugIndex = 0;
#else
	int debugIndex = 1;
#endif

	std::string libDir = pluginDir + dir;

	std::set<std::string> loadedLibs;

	std::vector<std::string> libs = listDirectory(libDir, false, ext);
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < libs.size(); i++) {
			std::string libName = libs[i];

			int found = libs[i].find(debugPostFix + ext);

			bool add = false;

			if (found != std::string::npos) {
				libName = libs[i].substr(0, found) + ext;
				add = debugIndex == j;
			}
			else {
				add = debugIndex != j;
			}

			if (add && loadedLibs.find(libName) == loadedLibs.end()) {
				loadedLibs.insert(libName);
				manager.loadPlugin(libDir + libs[i]);
			}
		}
	}


}


std::string IVPluginManager::getBinDirectory(const std::string& executable) const {
	std::size_t found = executable.find_last_of("/\\");
	return found != std::string::npos ? executable.substr(0,found) : ".";
}


void IVPluginManager::loadRelativePlugins(const std::string& executablePath, const std::string& relativePluginPath) {
	loadPlugins(getBinDirectory(executablePath) + relativePluginPath);
}

} /* namespace any_fw */


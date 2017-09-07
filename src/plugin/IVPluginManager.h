/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef IVPLUGINMANAGER_H_
#define IVPLUGINMANAGER_H_

#include "PluginManager.h"
#include <string>
#include <set>
#include <vector>
#include "factory/AnyItemFactory.h"

namespace IVGFX {

class IVPluginManager {
public:
	IVPluginManager();
	virtual ~IVPluginManager();

	template<typename T>
	void addAPI(T* api);

	void loadInstalledPlugins();
	void loadRelativePlugins(const std::string& executablePath, const std::string& relativePluginPath = "/../plugins");
	void loadPlugins(const std::string& pluginPath);

	const AnyItemFactory& getFactory() { return factory; }


private:
	void loadLibraries(const std::string& pluginDir);
	std::string getBinDirectory(const std::string& executable) const;

	PluginFW::PluginManager manager;
	std::set<std::string> loadedPlugins;
	std::vector<AnyItemFactory*> factories;
	CompositeAnyItemFactory factory;
};

} /* namespace IVGFX */

template<typename T>
inline void IVGFX::IVPluginManager::addAPI(T* api) {
	manager.addInterface(api);
}

#endif /* IVPLUGINMANAGER_H_ */

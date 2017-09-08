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
#include "factory/TypeGroupFactory.h"
#include "FactoryAPI.h"

namespace any_fw {

class IVPluginManager : public FactoryAPI {
public:
	IVPluginManager();
	virtual ~IVPluginManager();

	template<typename T>
	void addAPI(T* api);

	void loadInstalledPlugins();
	void loadRelativePlugins(const std::string& executablePath, const std::string& relativePluginPath = "/../plugins");
	void loadPlugins(const std::string& pluginPath);

	const TypeGroupFactory& getFactory() { return factory; }
	void addFactory(AnyItemFactory* factory);

private:
	void loadLibraries(const std::string& pluginDir);
	std::string getBinDirectory(const std::string& executable) const;

	PluginFW::PluginManager manager;
	std::set<std::string> loadedPlugins;
	TypeGroupFactory factory;
};

} /* namespace any_fw */

template<typename T>
inline void any_fw::IVPluginManager::addAPI(T* api) {
	manager.addInterface(api);
}

#endif /* IVPLUGINMANAGER_H_ */

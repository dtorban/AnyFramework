/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef IVPLUGIN_H_
#define IVPLUGIN_H_

#include "Plugin.h"
#include "PluginVersion.h"
#include "factory/AnyItemFactory.h"

namespace IVGFX {

class IVPlugin : public PluginFW::CompositePlugin {
public:
	IVPlugin() : CompositePlugin(std::vector<PluginFW::Plugin*>()) {}
	virtual ~IVPlugin() {}

	void initialize(const PluginFW::PluginInfo& info);
	void addFactory(AnyItemFactory* factory) {
		factories.push_back(factory);
	}

	const PluginFW::PluginInfo& getInfo() { return info; }

private:
	std::vector<AnyItemFactory*> factories;
	PluginFW::PluginInfo info;
};

class AnyFactoryPlugin : public PluginFW::TypedPlugin<std::vector<AnyItemFactory*> > {
public:
	AnyFactoryPlugin(std::vector<AnyItemFactory*>& factories) : factories(factories) {}
	virtual ~AnyFactoryPlugin() {}

	void registerPlugin(std::vector<AnyItemFactory*>& api, PluginFW::PluginAPIInfo& apiInfo) {
		for (int f = 0; f < factories.size(); f++) {
			api.push_back(factories[f]);
		}
	}
	void unregisterPlugin(std::vector<AnyItemFactory*>& api, PluginFW::PluginAPIInfo& apiInfo) {}

private:
	std::vector<AnyItemFactory*>& factories;
};


} /* namespace IVGFX */

inline void IVGFX::IVPlugin::initialize(const PluginFW::PluginInfo& info) {
	addPlugin(new AnyFactoryPlugin(factories));
	this->info = info;
	PluginFW::CompositePlugin::initialize(info);
}


#endif /* IVPLUGIN_H_ */

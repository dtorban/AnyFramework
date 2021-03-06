/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include <iostream>
#include "object/Object.h"
#include "AnyItem/impl/ReferenceCountedItem.h"

using namespace any;
using namespace any_fw;

class WidgetFactory : public any_fw::AnyItemTypeFactory {
public:
	WidgetFactory() : any_fw::AnyItemTypeFactory("Widget") {}
	any::AnyItem createItem(const any::AnyItem& query) const {
		any::AnyItem widget;
		widget["name"] = std::string("Widget");
		widget["components"].push(std::string("comp1"));
		widget["components"].push(3.14);
		widget["components"].push(any::AnyItem());
		widget["components"][2]["subComponet"] = 52;
		widget["ptr"] = new int(23);
		return widget;
	}
};

class GizmoFactory : public any_fw::AnyItemTypeFactory {
public:
	GizmoFactory() : any_fw::AnyItemTypeFactory("Gizmo") {}
	any::AnyItem createItem(const any::AnyItem& query) const {
		return any::ValueItem<double>(5.5);
	}
};

class ThingFactory : public any_fw::AnyItemTypeFactory {
public:
	ThingFactory() : any_fw::AnyItemTypeFactory("Thing") {
		parameters["Value"] = (double)0.0;
		parameters["Factory"] = static_cast<const AnyItemFactory*>(NULL);
	}
	any::AnyItem createItem(const any::AnyItem& query) const {
		any::AnyItem thing;
		thing.toArray();
		thing[10] = std::string("Item 10");
		thing[5]["name"] = std::string("five");
		thing[5]["value"] = 5;
		thing[5]["ptr"] = new int(5);
		thing[5]["array"].push(1).push(2).push(3).push(4).push(5);
		thing[0] = query["Value"].asType<double>()+0.1;

		if (!query["Factory"].isBlank()) {
			any::AnyItem subQuery;
			subQuery["Type"] = std::string("Widget");
			const AnyItemFactory* factory = query["Factory"].ptr<const AnyItemFactory*>();
			//thing[11]["test"] = item;
			any::AnyItem item = factory->create(subQuery);
			thing[1]["Widget"].set(item);
			subQuery["Type"] = std::string("Gizmo");
			item.set(factory->create(subQuery));
			thing[2]["Gizmo"].set(item);
		}

		return thing;
	}
};

class TestObject : public Object {
public:
	class Clear : public Method {
	public:
		Clear(Object& obj) : Method(obj, "clear") {
			parameters["test"] = std::string("Value");
		}
		any::AnyItem operator()(const any::AnyItem& parameters) {
			std::cout << obj.getProperties()["item3"] << std::endl;
			return any::AnyItem::blank();
		}
	};

	TestObject() : Object("TestObject") {
		properties["item1"] = 1;
		properties["item2"] = 2;
		properties["item3"] = 3;
		methods["clear"] = (new Clear(*this));
		methods["clear2"] = (new Clear(*this));
		addType<std::string>();
		addType<TestObject>();
	}
	~TestObject() {
		std::cout << "TestObject deleted." << std::endl;
	}
};

class TestObjectFactory : public any_fw::AnyItemTypeFactory {
public:
	TestObjectFactory() : any_fw::AnyItemTypeFactory("TestObject") {}
	any::AnyItem createItem(const any::AnyItem& query) const {
		return ValueItem<Object*>(new TestObject());
	}
};

extern "C"
{
	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new WidgetFactory());
		plugin->addFactory(new GizmoFactory());
		plugin->addFactory(new ThingFactory());
		plugin->addFactory(new TestObjectFactory());
		return plugin;
	}
}

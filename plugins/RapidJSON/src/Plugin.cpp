/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include <iostream>
#include <map>
#include "rapidjson/document.h"

using namespace rapidjson;

class JSONFactory : public any_fw::AnyItemTypeFactory {
public:
	JSONFactory() : any_fw::AnyItemTypeFactory("JSON") {
		parameters["Text"] = std::string("");
	}
	any::AnyItem createItem(const any::AnyItem& query) const {
		Document document;
		document.Parse(query["Text"].val<std::string>().c_str());

		any::AnyItem json;
		const Value& val = document;

		processItem(val, json);

		return json;
	}

	void processItem(const Value& val, any::AnyItem& item) const {
		if (val.IsObject()) {
			processObject(val, item);
		}
		else if (val.IsArray()) {
			processArray(val, item);
		}
		else if (val.IsNumber()) {
			item = val.GetDouble();
		}
		else if (val.IsTrue()) {
			item = std::string("true");
		}
		else if (val.IsFalse()) {
			item = std::string("false");
		}
		else if (val.IsString()) {
			item = std::string(val.GetString());
		}
	}

	void processObject(const Value& val, any::AnyItem& item) const {
		for (Value::ConstMemberIterator itr = val.MemberBegin(); itr != val.MemberEnd(); ++itr){
			item[itr->name.GetString()] = any::AnyItem();
			processItem(itr->value, item[itr->name.GetString()]);
		}
	}

	void processArray(const Value& val, any::AnyItem& item) const {
		for (Value::ConstValueIterator itr = val.Begin(); itr != val.End(); ++itr) {
			item.push(any::AnyItem());
			processItem(*itr, item[item.size() - 1]);
		}
	}
};

extern "C"
{
	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new JSONFactory());
		return plugin;
	}
}

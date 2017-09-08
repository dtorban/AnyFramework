/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include <iostream>
#include <rapidxml.hpp>
#include <map>

using namespace rapidxml;

class XMLFactory : public any_fw::AnyItemTypeFactory {
public:
	XMLFactory() : any_fw::AnyItemTypeFactory("XML") {
		parameters["Text"] = std::string("");
	}
	any::AnyItem createItem(const any::AnyItem& query) const {
		xml_document<> doc;    // character type defaults to char
		std::string instr = query["Text"].val<std::string>().c_str();
		std::vector<char> buffer = std::vector<char>(instr.begin(), instr.end());
		buffer.push_back('\0');
		doc.parse<0>(&buffer[0]); // 0 means default parse flags

		any::AnyItem xml;
		processNode(&doc, xml);

		return xml;
	}


	void processNode(xml_node<>* node, any::AnyItem& item) const {
		if (node->type() == node_element || node->type() == node_document) {
			std::map<std::string, int> childNames;

			for (xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
				if (childNames.find(child->name()) == childNames.end()) {
					childNames[std::string(child->name())] = 1;
				}
				else {
					childNames[std::string(child->name())] = childNames[std::string(child->name())]+1;
				}
			}

			for (std::map<std::string, int>::iterator it = childNames.begin(); it != childNames.end(); it++) {
				std::string name = it->first;
				if (it->second > 1) {
					item[name].toArray();
				}

				for (xml_node<> *child = node->first_node(it->first.c_str()); child; child = child->next_sibling(it->first.c_str())) {
					if (name.size() == 0) {
						processNode(child, item["value"]);
					}
					else if (it->second > 1) {
						item[name].push(any::AnyItem());
						processNode(child, item[name][item[name].size()-1]);
					}
					else {
						item[name].set(any::AnyItem());
						processNode(child, item[name]);
					}
				}
			}

		} else if (node->type() == node_data) {
			char* value = node->value();
			std::string val = value ? std::string(value, node->value_size()) : "";
			item = val;
		}

		for (xml_attribute<>* att = node->first_attribute(); att; att = att->next_attribute()) {
			std::string name = std::string(att->name(), att->name_size());
			char* value = att->value();
			std::string val = value ? std::string(value, att->value_size()) : "";
			item[name] = val;
		}
	}
};

extern "C"
{
	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new XMLFactory());
		return plugin;
	}
}

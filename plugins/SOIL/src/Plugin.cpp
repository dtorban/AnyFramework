/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */
#include "plugin/IVPlugin.h"
#include "SOIL.h"

	//image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

class SOILImageFactory : public any_fw::AnyItemTypeFactory {
public:
	SOILImageFactory() : any_fw::AnyItemTypeFactory("Image") {}
	any::AnyItem createItem(const any::AnyItem& params) const {
		std::string path = params["Path"].asType<std::string>();
		int width, height, depth, channels;
		unsigned char* soilImage = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

		width = width ? width : 1;
		height = height ? height : 1;
		depth = depth ? depth : 1;
		channels = channels ? channels : 1;

		any::AnyItem image;
		image["width"] = width;
		image["height"] = height;
		image["depth"] = depth;
		image["channels"] = channels;
		image["path"] = path;

		image["data"] =std::vector<unsigned char>();
		image["data"].val<std::vector<unsigned char> >().assign(soilImage, soilImage + width*height*depth*channels);

		SOIL_free_image_data( soilImage );
		return image;
	}
};

extern "C"
{
//int width, height, channels;
	//unsigned char* image;

	PLUGIN_API PluginFW::Plugin* loadFWPlugin() {
		any_fw::IVPlugin* plugin = new any_fw::IVPlugin();
		plugin->addFactory(new SOILImageFactory());
		return plugin;
	}
}

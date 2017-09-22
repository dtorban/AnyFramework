#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"
#include <cstdlib>

using namespace any;
using namespace any_fw;

int main(int argc, char**argv) {
	if (argc < 2) {
		std::cout << "Usage: AssetImportExample /path/to/asset_file" << std::endl;
		exit(0);
	}

	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	Object& assetImporter = *pm.getFactory().createType("AssetImporter").ptr<Object*>();
	AnyItem params = assetImporter.Methods["import"].getParameters();
	params["Path"] = std::string(argv[1]);
	AnyItem asset = assetImporter.Methods["import"](params);

	std::cout << assetImporter << std::endl;
	std::cout << asset << std::endl;
	if (!asset.isBlank()) {
		std::cout << *asset.ptr<Object*>() << std::endl;
		float val = asset.ptr<Object*>()->getProperties()["Meshes"][0]["Vertices"].val<std::vector<float> >()[0];
		std::cout << val << std::endl;
	}

	delete asset.ptr<Object*>();
	delete &assetImporter;

	return 0;
}



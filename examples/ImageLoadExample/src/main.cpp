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
		std::cout << "Usage: ImageLoadExample /path/to/image_file" << std::endl;
		exit(0);
	}

	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	AnyItem params;
	params["Path"] = std::string(argv[1]);
	AnyItem image = pm.getFactory().createType("Image", params);

	std::cout << image << std::endl;

	return 0;
}



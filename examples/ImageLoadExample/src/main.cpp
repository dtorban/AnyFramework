#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"
#include <cstdlib>

using namespace any;
using namespace any_fw;

float getLuminance(float r, float g, float b) {
	return 0.2126*r + 0.7152*g + 0.0722*b;
}

int getPixelLocation(int x, int y, int width, int height, int channels) {
	return (x + width*(y)) * channels;
}

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

	std::string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

	if (!image.isBlank()) {
		std::vector<unsigned char>& data = image["data"].val<std::vector<unsigned char> >();

		for (int y = 0; y < image["height"].val<int>(); y+=image["channels"].val<int>()) {
			for (int x = 0; x < image["width"].val<int>(); x+=image["channels"].val<int>()) {
				int loc = getPixelLocation(x, y, image["width"].val<int>(), image["height"].val<int>(), image["channels"].val<int>());
				float d = getLuminance(1.0*data[loc+0]/255.0, 1.0*data[loc+1]/255.0, 1.0*data[loc+2]/255.0);
				d =  d*(density.size()-1);
				std::cout << density[(int)d];
			}

			std::cout << std::endl;
		}
	}

	return 0;
}



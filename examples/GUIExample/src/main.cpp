#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"
#include <cstdlib>

using namespace any;
using namespace any_fw;

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	Object& gui = *pm.getFactory().createType("NanoGUIInterface").ptr<Object*>();

	std::cout << gui << std::endl;

	gui.Methods["init"]();
	Object& screen = *gui.Methods["createScreen"]().ptr<Object*>();
	std::cout << screen << std::endl;

	AnyItem params;
	params["type"] = std::string("Window");
	Object& window = *screen.Methods["createWidget"](params).ptr<Object*>();
	std::cout << window << std::endl;
	params["type"] = std::string("Button");
	window.Methods["createWidget"](params);

	screen.Methods["update"]();

	gui.Methods["mainloop"]();

	delete &screen;

	gui.Methods["shutdown"]();

	return 0;
}



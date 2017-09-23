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
	gui.Methods["createScreen"]();
	gui.Methods["mainloop"]();


	return 0;
}



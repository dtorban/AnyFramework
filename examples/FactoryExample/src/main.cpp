#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"

using namespace any;
using namespace any_fw;

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	std::cout << pm.getFactory() << std::endl;

	AnyItem params;
	AnyItem widget = pm.getFactory().createType("Widget");
	AnyItem gizmo = pm.getFactory().createType("Gizmo");
	params["Value"] = 757;
	AnyItem thing1 = pm.getFactory().createType("Thing", params);
	params["Value"] = std::string("600");
	params["Factory"] = (const AnyItemFactory*)&(pm.getFactory());
	AnyItem thing2 = pm.getFactory().createType("Thing", params);

	std::cout << "\n* Widget:\n\t" << widget << std::endl;
	std::cout << "\n* Gizmo:\n\t" << gizmo << std::endl;
	std::cout << "\n* Thing1:\n\t" << thing1 << std::endl;
	std::cout << "\n* Thing2:\n\t" << thing2 << std::endl;

	std::cout << "\n" << "thing1[0] as string: "<< thing1[0].asType<std::string>() << std::endl;
	std::cout << "thing2[0] as int: "<< thing2[0].asType<int>() << std::endl;
	std::cout << "thing1[5][\"ptr\"] value: "<< *thing1[5]["ptr"].ptr<int*>() << std::endl;
	std::cout << "widget[\"ptr\"] value: "<< *widget["ptr"].ptr<int*>() << std::endl;

	std::cout << std::endl;

	Object& obj = *pm.getFactory().createType("TestObject").ptr<Object*>();

	std::cout << obj << std::endl;
	params.set(obj.Methods["clear"].getParameters());
	std::cout << params << std::endl;
	obj.Methods["clear"](params);
	delete &obj;

	return 0;
}



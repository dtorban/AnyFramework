#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"

using namespace any;
using namespace IVGFX;

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	AnyItem query;
	query["Type"] = std::string("Widget");
	AnyItem widget = pm.getFactory().create(query);
	query["Type"] = std::string("Gizmo");
	AnyItem gizmo = pm.getFactory().create(query);
	query["Type"] = std::string("Thing");
	query["Value"] = 757;
	AnyItem thing1 = pm.getFactory().create(query);
	query["Value"] = std::string("600");
	query["Factory"] = (const AnyItemFactory*)&(pm.getFactory());
	AnyItem thing2 = pm.getFactory().create(query);

	std::cout << "\n* Widget:\n\t" << widget << std::endl;
	std::cout << "\n* Gizmo:\n\t" << gizmo << std::endl;
	std::cout << "\n* Thing1:\n\t" << thing1 << std::endl;
	std::cout << "\n* Thing2:\n\t" << thing2 << std::endl;

	std::cout << "\n" << "thing1[0] as string: "<< thing1[0].asType<std::string>() << std::endl;
	std::cout << "thing2[0] as int: "<< thing2[0].asType<int>() << std::endl;
	std::cout << "thing1[5][\"ptr\"] value: "<< *thing1[5]["ptr"].ptr<int*>() << std::endl;
	std::cout << "widget[\"ptr\"] value: "<< *widget["ptr"].ptr<int*>() << std::endl;

	std::cout << std::endl;

	AnyItem objectQuery;
	objectQuery["Type"] = std::string("TestObject");
	Object& obj = *pm.getFactory().create(objectQuery).ptr<Object*>();

	std::cout << obj << std::endl;
	AnyItem params = obj.Methods["clear"].getParameters();
	std::cout << params << std::endl;
	obj.Methods["clear"](params);
	delete &obj;

	return 0;
}



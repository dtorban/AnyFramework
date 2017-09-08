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

	std::cout << "\nXML Parse Example:" << std::endl;
	AnyItem params;
	params["Text"] = std::string(
			"<Item1>1</Item2>"
			"<Item2 again=\"blah\">"
			"	<sub again=\"blah2\">This is a test</sub>"
			"	<sub again=\"blah2\">This is a test2</sub>"
			"	<sub again=\"blah2\">This is a test3</sub>"
			"	<sub>"
			"		<sub2>to see if it works</sub2>"
			"	</sub>"
			"</Item2>"
			"<Item3>1</Item3>");
	AnyItem xml = pm.getFactory().createType("ParsedXML", params);
	std::cout << xml << std::endl;

	std::cout << "\nJSON Parse Example:" << std::endl;
	params["Text"] = std::string(
				"{"
				""
				"	\"hello\": \"world\","
				"	\"t\": true ,"
				"	\"f\": false,"
				"	\"n\": null,"
				"	\"i\": 123,"
				"	\"pi\": 3.1416,"
				"	\"a\": [1, 2, 3, 4],"
				"	\"obj\": {"
				"		\"abc\": \"test\","
				"		\"item\": 123"
				"	}"
				"}");
	AnyItem json = pm.getFactory().createType("ParsedJSON", params);
	std::cout << json << std::endl;

	return 0;
}



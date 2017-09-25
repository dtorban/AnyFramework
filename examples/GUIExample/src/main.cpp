#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"
#include <cstdlib>
#include "object/Callback.h"
#include <iostream>

using namespace any;
using namespace any_fw;

class SimpleCallback : public Callback {
public:
	void exec(const any::AnyItem& parameters) {
		std::cout << parameters << std::endl;
	}
};

std::string toPercentStr(float val) {
	int ival = ((int) (val * 100));
	std::stringstream ss;
	ss << ival;
	return std::string(ss.str());
}

class UpdateTextbox : public Callback {
public:
	UpdateTextbox(Object& textbox) : textbox(textbox) {}
	void exec(const any::AnyItem& parameters) {
		float val = parameters.val<float>();
		textbox.getProperties()["value"].val<std::string>() = toPercentStr(val);
		textbox.Methods["update"]();
	}

private:
	Object& textbox;
};

Object& createWidget(Object& parent, const std::string& type) {
	AnyItem params;
	params["type"] = std::string(type);
	Object& widget = parent.Methods["createWidget"](params).ref<Object>();
	std::cout << widget << std::endl;
	return widget;
}

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	Object& gui = pm.getFactory().createType("NanoGUIInterface").ref<Object>();

	std::cout << gui << std::endl;

	gui.Methods["init"]();
	Object& screen = *gui.Methods["createScreen"]().ptr<Object*>();
	std::cout << screen << std::endl;

	Object& window = createWidget(screen, "Window");//screen.Methods["createWidget"](params).ref<Object>();
	Object& button = createWidget(window, "Button");
	static SimpleCallback callback;
	button.Methods["setCallback"](any::ValueItem<Callback*>(&callback));
	Object& button2 = createWidget(window, "Button");
	Object& panel = createWidget(window, "Panel");
	Object& slider = createWidget(panel, "Slider");
	Object& textbox = createWidget(panel, "TextBox");
	textbox.getProperties()["value"].val<std::string>() = toPercentStr(slider.getProperties()["value"].val<float>());
	textbox.getProperties()["units"].val<std::string>() = std::string("%");
	textbox.Methods["update"]();
	UpdateTextbox updateTextbox(textbox);
	slider.Methods["setCallback"](any::ValueItem<Callback*>(&updateTextbox));

	screen.Methods["update"]();
	gui.Methods["mainloop"]();

	delete &screen;

	gui.Methods["shutdown"]();

	return 0;
}



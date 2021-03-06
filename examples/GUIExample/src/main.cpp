#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"
#include <cstdlib>
#include "object/Callback.h"
#include <iostream>
#include "OpenGL.h"

using namespace any;
using namespace any_fw;

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

class ResetSlider : public Callback {
public:
	ResetSlider(Object& slider, Object& textbox) : slider(slider), textbox(textbox) {}
	void exec(const any::AnyItem& parameters) {
		slider.getProperties()["value"].val<float>() = 0.0f;
		slider.Methods["update"]();
		textbox.getProperties()["value"].val<std::string>() = "0";
		textbox.Methods["update"]();
	}

private:
	Object& slider;
	Object& textbox;
};

class CanvasCallback : public Callback {
public:
	CanvasCallback(Object& slider) : slider(slider) {}
	void exec(const any::AnyItem& parameters) {
		glClearColor(slider.getProperties()["value"].val<float>(),0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
private:
	Object& slider;
};

class ScreenCallback : public Callback {
public:
	void exec(const any::AnyItem& parameters) {
		//glClearColor(0,0,1,1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
};

void initGL(IVPluginManager& pm) {
	Object* glfw = pm.getFactory().createType("GLFWInterface").ptr<Object*>();
	Object* window = glfw->Methods["createWindow"]().ptr<Object*>();
	window->Methods["makeCurrent"]();
	initializeGLEW();
	window->Methods["release"]();
	delete window;
	delete glfw;
}

Object& createWidget(Object& parent, const std::string& type, const std::string& title = "") {
	AnyItem params;
	params["type"] = std::string(type);
	if (title.length() > 0) {
		params["title"] = title;
	}
	Object& widget = parent.Methods["createWidget"](params).ref<Object>();
	std::cout << widget << std::endl;
	return widget;
}

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	Object* gui = pm.getFactory().createType("NanoGUIInterface").ptr<Object*>();
	std::cout << *gui << std::endl;

	// Initialize gl and gui
	initGL(pm);
	gui->Methods["init"]();

	// Create screen
	Object* screen = gui->Methods["createScreen"]().ptr<Object*>();
	std::cout << *screen << std::endl;

	// Create widgets
	Object& window = createWidget(*screen, "Window");
	Object& panel = createWidget(window, "Panel");
	Object& slider = createWidget(panel, "Slider");
	Object& textbox = createWidget(panel, "TextBox");
	Object& resetButton = createWidget(panel, "Button", "Reset");
	Object& canvas = createWidget(window, "GLCanvas");

	// Initialize properties
	textbox.getProperties()["value"].val<std::string>() = toPercentStr(slider.getProperties()["value"].val<float>());
	textbox.getProperties()["units"].val<std::string>() = std::string("%");
	textbox.Methods["update"]();

	// Add callbacks
	UpdateTextbox updateTextbox(textbox);
	ResetSlider resetCallback(slider, textbox);
	CanvasCallback canvasCallback(slider);
	ScreenCallback screenCallback;
	screen->Methods["setCallback"](any::ValueItem<Callback*>(&screenCallback));
	slider.Methods["setCallback"](any::ValueItem<Callback*>(&updateTextbox));
	resetButton.Methods["setCallback"](any::ValueItem<Callback*>(&resetCallback));
	canvas.Methods["setCallback"](any::ValueItem<Callback*>(&canvasCallback));

	// GUI methods
	screen->Methods["update"]();
	gui->Methods["mainloop"]();
	gui->Methods["shutdown"]();

	delete screen;
	delete gui;

	return 0;
}



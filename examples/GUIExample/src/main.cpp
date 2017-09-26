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
	CanvasCallback(Object& gl, Object& slider) : slider(slider), gl(gl) {}
	void exec(const any::AnyItem& parameters) {
		gl.Methods["glClearColor"].getParameters()[0].val<double>() = slider.getProperties()["value"].val<float>();
		gl.Methods["glClearColor"]();
		gl.Methods["glClear"]();
	}
private:
	Object& slider;
	Object& gl;
};

class ScreenCallback : public Callback {
public:
	ScreenCallback(Object& gl) : gl(gl) {
		clearParams.set(gl.Methods["glClearColor"].getParameters());
	}

	void exec(const any::AnyItem& parameters) {
		//clearParams[2].val<double>() = 1;
		//gl.Methods["setClearColor"](clearParams);
		//gl.Methods["clear"]();
	}
private:
	Object& gl;
	AnyItem clearParams;
};

void initGL(IVPluginManager& pm, Object& gl) {
	Object* glfw = pm.getFactory().createType("GLFWInterface").ptr<Object*>();
	Object* window = glfw->Methods["createWindow"]().ptr<Object*>();
	window->Methods["makeCurrent"]();
	gl.Methods["init"]();
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
	Object* gl = pm.getFactory().createType("OpenGLInterface").ptr<Object*>();

	std::cout << *gui << std::endl;

	// Initialize gl and gui
	initGL(pm, *gl);
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
	CanvasCallback canvasCallback(*gl, slider);
	ScreenCallback screenCallback(*gl);
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
	delete gl;

	return 0;
}



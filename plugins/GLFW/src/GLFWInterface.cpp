/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GLFWInterface.h>
#include <GLFW/glfw3.h>
#include "GLFWWindow.h"

namespace any_fw {

static void error_callback(int error, const char* description) {
	std::cout << "Error: " << description << std::endl;
}

class GLFWCreateWindow : public Object::Method {
public:
	GLFWCreateWindow(Object& obj) : Method(obj, "createWindow") {
		parameters["Width"] = 400;
		parameters["Height"] = 400;
		parameters["XPos"] = 0;
		parameters["YPos"] = 0;
		parameters["Title"] = std::string("");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		return any::ValueItem<GLFWWindow*>(new GLFWWindow(parameters));
	}
};

class GLFWPollEvents : public Object::Method {
public:
	GLFWPollEvents(Object& obj) : Method(obj, "pollEvents") {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glfwPollEvents();
		return any::AnyItem::blank();
	}
};

GLFWInterface::GLFWInterface(const any::AnyItem& anyItem) : Object("GLFWInterface") {
	methods["pollEvents"] = new GLFWPollEvents(*this);
	methods["createWindow"] = new GLFWCreateWindow(*this);

	glfwSetErrorCallback(error_callback);

	if( !glfwInit() ) {
		std::cout << "Error initializing GLFW" << std::endl;
	}
}

GLFWInterface::~GLFWInterface() {
	glfwTerminate();
}



} /* namespace any_fw */

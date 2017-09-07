/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "OpenGLInterface.h"
#include "OpenGLHeaders.h"

namespace IVGFX {

OpenGLInterface::OpenGLInterface(const any::AnyItem& anyItem) : Object("OpenGLInterface") {
	initMethods();
}

OpenGLInterface::~OpenGLInterface() {
}

class OpenGLMethod : public Object::Method {
protected:
	OpenGLMethod(OpenGLInterface& gl, const std::string& name) : Method(gl, name), gl(gl) {}
	OpenGLInterface& gl;
};

class OpenGLSetClearColor : public OpenGLMethod {
public:
	OpenGLSetClearColor(OpenGLInterface& gl) : OpenGLMethod(gl, "setClearColor") {
		parameters.toArray();
		parameters[0] = (double)0.0;
		parameters[1] = (double)0.0;
		parameters[2] = (double)0.0;
		parameters[3] = (double)1.0;
	}

	any::AnyItem operator()(const any::AnyItem& parameters) {
		glClearColor(parameters[0].val<double>(), parameters[1].val<double>(), parameters[2].val<double>(), parameters[3].val<double>());
		return any::AnyItem::blank();
	}
};

class OpenGLClear : public OpenGLMethod {
public:
	OpenGLClear(OpenGLInterface& gl) : OpenGLMethod(gl, "clear") {
		parameters["Color"] = 1;
		parameters["Depth"] = 1;
		parameters["Stencil"] = 1;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		GLuint clearBuffer = 0;
		if (parameters["Color"].val<int>()) {
			clearBuffer = clearBuffer | GL_COLOR_BUFFER_BIT;
		}
		if (parameters["Depth"].val<int>()) {
			clearBuffer = clearBuffer | GL_DEPTH_BUFFER_BIT;
		}
		if (parameters["Stencil"].val<int>()) {
			clearBuffer = clearBuffer | GL_STENCIL_BUFFER_BIT;
		}
		glClear(clearBuffer);
		return any::AnyItem::blank();
	}
};

void OpenGLInterface::initMethods() {
	addMethod(new OpenGLSetClearColor(*this));
	addMethod(new OpenGLClear(*this));
}

void OpenGLInterface::addMethod(Object::Method* method) {
	methods[method->getName()] = method;
}

} /* namespace IVGFX */

#ifndef OPENGLMETHODS_H_
#define OPENGLMETHODS_H_

#include "object/Object.h"

namespace any_fw {

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
		parameters["color"] = 1;
		parameters["depth"] = 1;
		parameters["stencil"] = 1;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		GLuint clearBuffer = 0;
		if (parameters["color"].val<int>()) {
			clearBuffer = clearBuffer | GL_COLOR_BUFFER_BIT;
		}
		if (parameters["depth"].val<int>()) {
			clearBuffer = clearBuffer | GL_DEPTH_BUFFER_BIT;
		}
		if (parameters["stencil"].val<int>()) {
			clearBuffer = clearBuffer | GL_STENCIL_BUFFER_BIT;
		}
		glClear(clearBuffer);
		return any::AnyItem::blank();
	}
};

class OpenGLEnable : public OpenGLMethod {
public:
	OpenGLEnable(OpenGLInterface& gl) : OpenGLMethod(gl, "enable") {
		parameters.set(any::ValueItem<unsigned int>(0));
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glEnable(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLDisable : public OpenGLMethod {
public:
	OpenGLDisable(OpenGLInterface& gl) : OpenGLMethod(gl, "disable") {
		parameters = (unsigned int)0;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glEnable(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLGetEnum : public OpenGLMethod {
public:
	OpenGLGetEnum(OpenGLInterface& gl) : OpenGLMethod(gl, "getEnum") {
		parameters = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		std::string& enumName = parameters.val<std::string>();
		GLuint enumVal = 0;

		if (enumName == "GL_CULL_FACE") {
			enumVal = GL_CULL_FACE;
		}

		return any::ValueItem<unsigned int>(enumVal);
	}
};

}


#endif

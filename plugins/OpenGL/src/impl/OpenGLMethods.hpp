#ifndef OPENGLMETHODS_H_
#define OPENGLMETHODS_H_

#include "object/Object.h"
#include "OpenGLShaderProgram.h"

namespace any_fw {


class OpenGLInit : public OpenGLMethod {
public:
	OpenGLInit(OpenGLInterface& gl) : OpenGLMethod(gl, "init") {
	}

	any::AnyItem operator()(const any::AnyItem& parameters) {
//		glewExperimental = GL_TRUE;
//		GLenum err = glewInit();
//		if (GLEW_OK != err) {
//			std::cout << "Error initializing GLEW." << std::endl;
//		}
		initializeGLEW();

		return any::AnyItem::blank();
	}
};

class OpenGLGetEnum : public OpenGLMethod {
public:
	OpenGLGetEnum(OpenGLInterface& gl) : OpenGLMethod(gl, "getEnum") {
		parameters = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		std::map<std::string, unsigned int>::iterator it = gl.glEnums.find(parameters.val<std::string>());
		unsigned int e = GL_NONE;
		if (it != gl.glEnums.end()) {
			e = it->second;
		}
		else {
			std::cout << "Could not find enum: " << parameters.val<std::string>() << std::endl;
		}
		return any::ValueItem<unsigned int>(e);
	}
};

class OpenGLSetClearColor : public OpenGLMethod {
public:
	OpenGLSetClearColor(OpenGLInterface& gl) : OpenGLMethod(gl, "glClearColor") {
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
	OpenGLClear(OpenGLInterface& gl) : OpenGLMethod(gl, "glClear") {
		parameters = (unsigned int)(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glClear(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLEnable : public OpenGLMethod {
public:
	OpenGLEnable(OpenGLInterface& gl) : OpenGLMethod(gl, "glEnable") {
		parameters = (unsigned int)(GL_NONE);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glEnable(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLDisable : public OpenGLMethod {
public:
	OpenGLDisable(OpenGLInterface& gl) : OpenGLMethod(gl, "glDisable") {
		parameters = (unsigned int)(GL_NONE);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glDisable(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLSetCullMode : public OpenGLMethod {
public:
	OpenGLSetCullMode(OpenGLInterface& gl) : OpenGLMethod(gl, "glCullFace") {
		parameters = (unsigned int)(GL_NONE);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glCullFace(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLSetBlendFunction : public OpenGLMethod {
public:
	OpenGLSetBlendFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "glBlendFunc") {
		parameters[0] = (unsigned int)(GL_NONE);
		parameters[1] = (unsigned int)(GL_NONE);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glBlendFunc(parameters[0].val<unsigned int>(), parameters[1].val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLSetBlendFunctioni : public OpenGLMethod {
public:
	OpenGLSetBlendFunctioni(OpenGLInterface& gl) : OpenGLMethod(gl, "glBlendFunci") {
		parameters.toArray();
		parameters[0].set(any::AnyItem::blank());
		parameters[1] = (unsigned int)(GL_NONE);
		parameters[2] = (unsigned int)(GL_NONE);
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glBlendFunci(parameters[0].val<unsigned int>(), parameters[1].val<unsigned int>(), parameters[2].val<unsigned int>());
		return any::AnyItem::blank();
	}
};


class OpenGLSetDepthFunction : public OpenGLMethod {
public:
	OpenGLSetDepthFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "glDepthFunc") {
		parameters = (unsigned int)GL_NONE;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glDepthFunc(parameters.val<unsigned int>());

		return any::AnyItem::blank();
	}
};


class OpenGLSetStencilFunction : public OpenGLMethod {
public:
	OpenGLSetStencilFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "glStencilFunc") {
		parameters.toArray();
		parameters[0] = (unsigned int)GL_NONE;
		parameters[1] = (int)0;
		parameters[2] = (unsigned int)0;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilFunc(parameters[0].val<unsigned int>(),
				parameters[1].val<int>(),
				parameters[2].val<unsigned int>());

		return any::AnyItem::blank();
	}
};

class OpenGLSetStencilMask : public OpenGLMethod {
public:
	OpenGLSetStencilMask(OpenGLInterface& gl) : OpenGLMethod(gl, "glStencilMask") {
		parameters = (unsigned int)0;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilMask(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLSetStencilOp : public OpenGLMethod {
public:
	OpenGLSetStencilOp(OpenGLInterface& gl) : OpenGLMethod(gl, "glStencilOp") {
		parameters.toArray();
		parameters[0] = (unsigned int)GL_NONE;
		parameters[1] = (unsigned int)GL_NONE;
		parameters[2] = (unsigned int)GL_NONE;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilOp(parameters[0].val<unsigned int>(),
				parameters[1].val<unsigned int>(),
				parameters[2].val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLCreateShaderProgram : public OpenGLMethod {
public:
	OpenGLCreateShaderProgram(OpenGLInterface& gl) : OpenGLMethod(gl, "createShaderProgram") {
		//parameters["Text"] = std::string("");
		//parameters["shaderType"] = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		return any::ValueItem<OpenGLShaderProgram*>(new OpenGLShaderProgram(gl));
	}
};

}


#endif

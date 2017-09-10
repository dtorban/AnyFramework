#ifndef OPENGLMETHODS_H_
#define OPENGLMETHODS_H_

#include "object/Object.h"
#include "OpenGLShaderProgram.h"

namespace any_fw {

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
		parameters["accum"] = 0;
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
		if (parameters["accum"].val<int>()) {
			clearBuffer = clearBuffer | GL_ACCUM_BUFFER_BIT;
		}
		glClear(clearBuffer);
		return any::AnyItem::blank();
	}
};

class OpenGLEnable : public OpenGLMethod {
public:
	OpenGLEnable(OpenGLInterface& gl) : OpenGLMethod(gl, "enable") {
		parameters = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glEnable(gl.glEnums[parameters.val<std::string>()]);
		return any::AnyItem::blank();
	}
};

class OpenGLDisable : public OpenGLMethod {
public:
	OpenGLDisable(OpenGLInterface& gl) : OpenGLMethod(gl, "disable") {
		parameters = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glEnable(gl.glEnums[parameters.val<std::string>()]);
		return any::AnyItem::blank();
	}
};

class OpenGLSetCullMode : public OpenGLMethod {
public:
	OpenGLSetCullMode(OpenGLInterface& gl) : OpenGLMethod(gl, "setCullMode") {
		parameters = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glCullFace(gl.glEnums[parameters.val<std::string>()]);
		return any::AnyItem::blank();
	}
};

class OpenGLSetBlendFunction : public OpenGLMethod {
public:
	OpenGLSetBlendFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "setBlendFunction") {
		parameters["sfactor"] = std::string("GL_NONE");
		parameters["dfactor"] = std::string("GL_NONE");
		parameters["buffer"].set(any::AnyItem::blank());
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		if (!parameters["buffer"].isBlank()) {
			glBlendFunci(parameters["buffer"].val<unsigned int>(), gl.glEnums[parameters["sfactor"].val<std::string>()], gl.glEnums[parameters["dfactor"].val<std::string>()]);
		}
		else {
			glBlendFunc(gl.glEnums[parameters["sfactor"].val<std::string>()], gl.glEnums[parameters["dfactor"].val<std::string>()]);
		}

		return any::AnyItem::blank();
	}
};

class OpenGLSetDepthFunction : public OpenGLMethod {
public:
	OpenGLSetDepthFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "setDepthFunction") {
		parameters["func"] = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glDepthFunc(gl.glEnums[parameters["func"].val<std::string>()]);

		return any::AnyItem::blank();
	}
};


class OpenGLSetStencilFunction : public OpenGLMethod {
public:
	OpenGLSetStencilFunction(OpenGLInterface& gl) : OpenGLMethod(gl, "setStencilFunction") {
		parameters["func"] = std::string("GL_NONE");
		parameters["ref"] = (int)0;
		parameters["mask"] = (unsigned int)0;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilFunc(gl.glEnums[parameters["func"].val<std::string>()],
				parameters["ref"].val<int>(),
				parameters["mask"].val<unsigned int>());

		return any::AnyItem::blank();
	}
};

class OpenGLSetStencilMask : public OpenGLMethod {
public:
	OpenGLSetStencilMask(OpenGLInterface& gl) : OpenGLMethod(gl, "setStencilMask") {
		parameters = (unsigned int)0;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilMask(parameters.val<unsigned int>());
		return any::AnyItem::blank();
	}
};

class OpenGLSetStencilOp : public OpenGLMethod {
public:
	OpenGLSetStencilOp(OpenGLInterface& gl) : OpenGLMethod(gl, "setStencilOp") {
		parameters["sfail"] = std::string("GL_NONE");
		parameters["dpfail"] = std::string("GL_NONE");
		parameters["dppass"] = std::string("GL_NONE");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		glStencilOp(gl.glEnums[parameters["sfail"].val<std::string>()],
				gl.glEnums[parameters["dpfail"].val<std::string>()],
				gl.glEnums[parameters["dppass"].val<std::string>()]);
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

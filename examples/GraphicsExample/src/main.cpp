#include <iostream>
#include <string>
#include "AnyItem/AnyItem.h"
#include "plugin/IVPluginManager.h"
#include "object/Object.h"

using namespace any;
using namespace any_fw;

void initContext(Object& window, Object& gl);
void renderOnWindow(Object& window, Object& gl);

int main(int argc, char**argv) {
	IVPluginManager pm;
	pm.loadRelativePlugins(argv[0]);
	pm.loadInstalledPlugins();

	AnyItem query;
	Object& glfw = *pm.getFactory().createType("GLFWInterface").ptr<Object*>();
	Object& gl = *pm.getFactory().createType("OpenGLInterface").ptr<Object*>();

	std::cout << glfw << std::endl;
	std::cout << gl << std::endl;

	gl.Methods["setClearColor"].getParameters()[0].val<double>() = 1.0;

	std::vector<Object*> windows;

	AnyItem params = glfw.Methods["createWindow"].getParameters();
	params["Width"] = 500;
	params["Height"] = 500;
	params["Title"] = std::string("Graphics Window");
	Object& window1 = *glfw.Methods["createWindow"](params).ptr<Object*>();
	params["XPos"] = 500;
	Object& window2 = *glfw.Methods["createWindow"](params).ptr<Object*>();

	initContext(window1, gl);
	initContext(window2, gl);

	while(true) {
		glfw.Methods["pollEvents"]();
		renderOnWindow(window1, gl);
		renderOnWindow(window2, gl);
		window1.Methods["swapBuffers"]();
		window2.Methods["swapBuffers"]();
	}

	delete &glfw;
	delete &gl;

	return 0;
}

void initContext(Object& window, Object& gl) {
	window.Methods["makeCurrent"]();

	gl.Methods["init"]();

	Object& shaderProgram = *gl.Methods["createShaderProgram"]().ptr<Object*>();
	std::cout << shaderProgram << std::endl;
	AnyItem vsh;
	vsh["shaderType"] = std::string("GL_VERTEX_SHADER");
	vsh["text"] = std::string(
				"#version 330\n"
				"layout(location = 0) in vec3 position;\n"
				"void main() {\n"
				"    gl_Position = vec4(position, 1.0);\n"
				"}\n");

	shaderProgram.Methods["setShader"](vsh);

	gl.Methods["setClearColor"]();
	window.Methods["release"]();
}

void renderOnWindow(Object& window, Object& gl) {
	window.Methods["makeCurrent"]();
	gl.Methods["clear"]();
	window.Methods["release"]();
}

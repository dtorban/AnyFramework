/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GLFWWindow.h>

namespace IVGFX {

class GLFWWindowMethod : public Object::Method {
protected:
	GLFWWindowMethod(GLFWWindow& window, const std::string& name) : Method(window, name), window(window) {}
	GLFWWindow& window;
};

class GLFWWindowClose : public GLFWWindowMethod {
public:
	GLFWWindowClose(GLFWWindow& window) : GLFWWindowMethod(window, "close") {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		window.close();
		return any::AnyItem::blank();
	}
};

class GLFWWindowMakeCurrent : public GLFWWindowMethod {
public:
	GLFWWindowMakeCurrent(GLFWWindow& window) : GLFWWindowMethod(window, "makeCurrent") {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		window.makeCurrent();
		return any::AnyItem::blank();
	}
};

class GLFWWindowRelease : public GLFWWindowMethod {
public:
	GLFWWindowRelease(GLFWWindow& window) : GLFWWindowMethod(window, "release") {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		window.release();
		return any::AnyItem::blank();
	}
};

class GLFWWindowSwapBuffers : public GLFWWindowMethod {
public:
	GLFWWindowSwapBuffers(GLFWWindow& window) : GLFWWindowMethod(window, "swapBuffers") {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		window.swapBuffers();
		return any::AnyItem::blank();
	}
};

void glfw_window_close_callback(GLFWwindow* window) {
	GLFWWindow& win = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
	win.close();
}

GLFWWindow::GLFWWindow(const any::AnyItem& settings) : Object("GLFWWindow") {
	window = glfwCreateWindow(
			settings["Width"].asType<int>(),
			settings["Height"].asType<int>(),
			settings["Title"].val<std::string>().c_str(),
			NULL,
			NULL );
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetWindowPos(window, settings["XPos"].asType<int>(), settings["YPos"].asType<int>());
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	methods["close"] = new GLFWWindowClose(*this);
	methods["swapBuffers"] = new GLFWWindowSwapBuffers(*this);
	methods["makeCurrent"] = new GLFWWindowMakeCurrent(*this);
	methods["release"] = new GLFWWindowRelease(*this);
	glfwMakeContextCurrent(NULL);
}

GLFWWindow::~GLFWWindow() {
	close();
}

void GLFWWindow::close() {
	if (window) {
		glfwDestroyWindow(window);
	}

	window = NULL;
}

void GLFWWindow::swapBuffers() {
	if (window) {
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
		// Place holder for now
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwMakeContextCurrent(NULL);
	}
}

void GLFWWindow::makeCurrent() {
	if (window) {
		glfwMakeContextCurrent(window);
	}
}

void GLFWWindow::release() {
	glfwMakeContextCurrent(NULL);
}

} /* namespace IVGFX */

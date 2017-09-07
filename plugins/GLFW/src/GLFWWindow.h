/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef GLFWWINDOW_H_
#define GLFWWINDOW_H_

#include "object/Object.h"
#include <GLFW/glfw3.h>


namespace any {
template<>
struct item_delete<GLFWwindow*> { static void destroy(GLFWwindow* item) {  } };
}

namespace any_fw {

class GLFWWindow : public Object {
public:
	GLFWWindow(const any::AnyItem& settings);
	virtual ~GLFWWindow();

	void close();
	void swapBuffers();
	void makeCurrent();
	void release();

private:
	GLFWwindow* window;
};

} /* namespace any_fw */

#endif /* GLFWWINDOW_H_ */

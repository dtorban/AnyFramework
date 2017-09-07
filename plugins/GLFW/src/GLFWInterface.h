/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef GLFWINTERFACE_H_
#define GLFWINTERFACE_H_

#include "object/Object.h"

namespace IVGFX {

class GLFWInterface : public Object {
public:
	GLFWInterface(const any::AnyItem& anyItem);
	virtual ~GLFWInterface();
};

} /* namespace IVGFX */

#endif /* GLFWINTERFACE_H_ */

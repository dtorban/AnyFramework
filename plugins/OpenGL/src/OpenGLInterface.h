/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef OPENGLINTERFACE_H_
#define OPENGLINTERFACE_H_

#include "object/Object.h"
#include "OpenGLHeaders.h"
#include <map>

namespace any_fw {

class OpenGLInterface : public Object {
public:
	OpenGLInterface(const any::AnyItem& anyItem);
	virtual ~OpenGLInterface();

	void initMethods();

	std::map<std::string, unsigned int> glEnums;
};

class OpenGLMethod : public Object::Method {
protected:
	OpenGLMethod(OpenGLInterface& gl, const std::string& name) : Method(gl, name), gl(gl) {}
	OpenGLInterface& gl;
};

} /* namespace any_fw */

#endif /* OPENGLINTERFACE_H_ */

/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "OpenGLInterface.h"
#include "OpenGLHeaders.h"
#include "impl/OpenGLMethods.hpp"

namespace any_fw {

OpenGLInterface::OpenGLInterface(const any::AnyItem& anyItem) : Object("OpenGLInterface") {
	initMethods();
}

OpenGLInterface::~OpenGLInterface() {
}

void OpenGLInterface::initMethods() {
	addMethod(new OpenGLSetClearColor(*this));
	addMethod(new OpenGLClear(*this));
	addMethod(new OpenGLEnable(*this));
	addMethod(new OpenGLDisable(*this));
	addMethod(new OpenGLGetEnum(*this));
}

void OpenGLInterface::addMethod(Object::Method* method) {
	methods[method->getName()] = method;
}

} /* namespace any_fw */

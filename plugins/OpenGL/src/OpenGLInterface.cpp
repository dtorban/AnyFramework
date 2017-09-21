/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "OpenGLInterface.h"
#include "impl/OpenGLMethods.hpp"

namespace any_fw {

OpenGLInterface::OpenGLInterface(const any::AnyItem& anyItem) : Object("OpenGLInterface") {
	initMethods();

	glEnums["GL_FRONT_AND_BACK"] = GL_FRONT_AND_BACK;
	glEnums["GL_FRONT"] = GL_FRONT;
	glEnums["GL_BACK"] = GL_BACK;
	glEnums["GL_NONE"] = GL_NONE;
	glEnums["GL_ZERO"] = GL_ZERO;
	glEnums["GL_ONE"] = GL_ONE;
	glEnums["GL_SRC_COLOR"] = GL_SRC_COLOR;
	glEnums["GL_ONE_MINUS_DST_COLOR"] = GL_ONE_MINUS_DST_COLOR;
	glEnums["GL_SRC_ALPHA"] = GL_SRC_ALPHA;
	glEnums["GL_ONE_MINUS_SRC_ALPHA"] = GL_ONE_MINUS_SRC_ALPHA;
	glEnums["GL_DST_ALPHA"] = GL_DST_ALPHA;
	glEnums["GL_ONE_MINUS_DST_ALPHA"] = GL_ONE_MINUS_DST_ALPHA;
	glEnums["GL_CONSTANT_COLOR"] = GL_CONSTANT_COLOR;
	glEnums["GL_ONE_MINUS_CONSTANT_COLOR"] = GL_ONE_MINUS_CONSTANT_COLOR;
	glEnums["GL_CONSTANT_ALPHA"] = GL_CONSTANT_ALPHA;
	glEnums["GL_ONE_MINUS_CONSTANT_ALPHA"] = GL_ONE_MINUS_CONSTANT_ALPHA;
	glEnums["GL_CULL_FACE"] = GL_CULL_FACE;
	glEnums["GL_DEPTH_TEST"] = GL_DEPTH_TEST;
	glEnums["GL_BLEND"] = GL_BLEND;
	glEnums["GL_STENCIL_TEST"] = GL_STENCIL_TEST;
	glEnums["GL_NEVER"] = GL_NEVER;
	glEnums["GL_LESS"] = GL_LESS;
	glEnums["GL_LEQUAL"] = GL_LEQUAL;
	glEnums["GL_GREATER"] = GL_GREATER;
	glEnums["GL_GEQUAL"] = GL_GEQUAL;
	glEnums["GL_EQUAL"] = GL_EQUAL;
	glEnums["GL_NOTEQUAL"] = GL_NOTEQUAL;
	glEnums["GL_ALWAYS"] = GL_ALWAYS;
	glEnums["GL_KEEP"] = GL_KEEP;
	glEnums["GL_ZERO"] = GL_ZERO;
	glEnums["GL_REPLACE"] = GL_REPLACE;
	glEnums["GL_INCR"] = GL_INCR;
	glEnums["GL_INCR_WRAP"] = GL_INCR_WRAP;
	glEnums["GL_DECR"] = GL_DECR;
	glEnums["GL_DECR_WRAP"] = GL_DECR_WRAP;
	glEnums["GL_INVERT"] = GL_INVERT;
	glEnums["GL_VERTEX_SHADER"] = GL_VERTEX_SHADER;
	glEnums["GL_FRAGMENT_SHADER"] = GL_VERTEX_SHADER;

}

OpenGLInterface::~OpenGLInterface() {
}

void OpenGLInterface::initMethods() {
	addMethod(new OpenGLInit(*this));
	addMethod(new OpenGLSetClearColor(*this));
	addMethod(new OpenGLClear(*this));
	addMethod(new OpenGLEnable(*this));
	addMethod(new OpenGLDisable(*this));
	addMethod(new OpenGLSetCullMode(*this));
	addMethod(new OpenGLSetBlendFunction(*this));
	addMethod(new OpenGLSetDepthFunction(*this));
	addMethod(new OpenGLSetStencilFunction(*this));
	addMethod(new OpenGLSetStencilMask(*this));
	addMethod(new OpenGLSetStencilOp(*this));
	addMethod(new OpenGLCreateShaderProgram(*this));
}


} /* namespace any_fw */

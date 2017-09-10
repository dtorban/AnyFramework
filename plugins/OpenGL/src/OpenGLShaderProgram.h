/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef OPENGLSHADERPROGRAM_H_
#define OPENGLSHADERPROGRAM_H_

#include "OpenGLInterface.h"
#include <map>

namespace any_fw {

class OpenGLShaderProgram : public Object {
public:
	OpenGLShaderProgram(OpenGLInterface& gl);
	virtual ~OpenGLShaderProgram();

	bool checkShaderCompileStatus(GLuint obj);
	void compileShader(const GLuint &shader, const std::string& code);
	void setShader(const GLuint &shaderType, const std::string& code);

private:
	OpenGLInterface& gl;
	std::map<GLuint, GLuint> shaders;
};

} /* namespace any_fw */

#endif /* OPENGLSHADERPROGRAM_H_ */

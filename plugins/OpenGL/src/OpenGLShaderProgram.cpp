/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <OpenGLShaderProgram.h>

namespace any_fw {

class OpenGLSetShader : public OpenGLMethod {
public:
	OpenGLSetShader(OpenGLInterface& gl, OpenGLShaderProgram& program) : OpenGLMethod(gl, "setShader"), program(program) {
		parameters["shaderType"] = std::string("GL_NONE");
		parameters["Text"] = std::string("");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		program.setShader(gl.glEnums[parameters["shaderType"].val<std::string>()],
				parameters["shaderType"].val<std::string>());
		return any::AnyItem::blank();
	}

private:
	OpenGLShaderProgram& program;
};

OpenGLShaderProgram::OpenGLShaderProgram(OpenGLInterface& gl) : Object("OpenGLShaderProgram"), gl(gl) {
	Method* method = new OpenGLSetShader(gl, *this);
	methods[method->getName()] = method;
}

OpenGLShaderProgram::~OpenGLShaderProgram() {
}

void OpenGLShaderProgram::compileShader(const GLuint &shader, const std::string& code)
{
	const char *source;
	int length;

	source = code.c_str();
	length = code.size();
	glShaderSource(shader, 1, &source, &length);
	glCompileShader(shader);
	if (!checkShaderCompileStatus(shader)) {
	}
}

bool OpenGLShaderProgram::checkShaderCompileStatus(GLuint obj) {
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

void OpenGLShaderProgram::setShader(const GLuint& shaderType,
		const std::string& code) {

	std::map<GLuint, GLuint>::iterator it = shaders.find(shaderType);
	if (it != shaders.end()) {
		glDeleteShader(it->second);
	}

	GLuint shader = glCreateShader(shaderType);
	compileShader(shader, code);
	shaders[shaderType] = shader;

}

} /* namespace any_fw */

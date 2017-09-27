/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef OPENGLHEADERS_H_
#define OPENGLHEADERS_H_

#include "GL/glew.h"
#ifdef _WIN32
#include "GL/wglew.h"
#elif (!defined(__APPLE__))
#include "GL/glxew.h"
#endif

#if defined(WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#elif defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

inline void initializeGLEW() {
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Error initializing GLEW." << std::endl;
	}
}

#endif /* OPENGLHEADERS_H_ */

#------------------------------------------
# Project
#------------------------------------------

project(OpenGL)

set (SOURCEFILES 
	src/Plugin.cpp
	src/OpenGLInterface.cpp
	src/OpenGLShaderProgram.cpp
)

set (HEADERFILES
)

#------------------------------------------
# Include Directories
#------------------------------------------

# Include Directories
include_directories (
  src
)

#------------------------------------------
# Download dependencies
#------------------------------------------

set(USE_GLEW True)
include(${CMAKE_SOURCE_DIR}/third-party/OpenGL/OpenGL.cmake)

#------------------------------------------
# Plugin
#------------------------------------------
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)

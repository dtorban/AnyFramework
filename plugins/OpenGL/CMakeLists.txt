#------------------------------------------
# Project
#------------------------------------------

project(OpenGL)

set (SOURCEFILES 
	src/Plugin.cpp
	src/OpenGLInterface.cpp
	src/OpenGLShaderProgram.cpp
	src/glew.cpp  
#  ${dependency_dir}/GLEW/src/src
)

set (HEADERFILES
)

#------------------------------------------
# Include Directories
#------------------------------------------

# Include Directories
include_directories (
  src
  ${dependency_dir}/GLEW/src/include
  ${dependency_dir}/GLEW/src/src
)

#------------------------------------------
# Download dependencies
#------------------------------------------

# OpenGL
find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})

set(ALL_LIBS ${OPENGL_LIBRARIES} ${ALL_LIBS})

set(DepName GLEW)
set(${DepName}_URL "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download")
set(${DepName}_HEADER_ONLY True)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

set(PROJECT_DEPS GLEW)

#------------------------------------------
# Plugin
#------------------------------------------
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)

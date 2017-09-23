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

include(${CMAKE_SOURCE_DIR}/third-party/OpenGL/OpenGL.cmake)

set(DepName GLEW)
set(${DepName}_URL "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download")
set(${DepName}_HEADER_ONLY True)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

#------------------------------------------
# Plugin
#------------------------------------------
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)

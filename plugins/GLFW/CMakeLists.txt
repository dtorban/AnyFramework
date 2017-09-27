#------------------------------------------
# Project
#------------------------------------------

project(GLFW)

set (SOURCEFILES 
	src/Plugin.cpp
	src/GLFWInterface.cpp
	src/GLFWWindow.cpp
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

set(DepName GLFWLib)
set(${DepName}_GIT_REPOSITORY "https://github.com/glfw/glfw.git")
set(${DepName}_LIB_NAME glfw3)
set(${DepName}_CMAKE_ARGS -DCMAKE_DEBUG_POSTFIX=d)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)
include(${CMAKE_SOURCE_DIR}/third-party/OpenGL/OpenGL.cmake)

#------------------------------------------
# Plugin
#------------------------------------------
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
#------------------------------------------
# Project
#------------------------------------------

project(NanoGUI)

set (SOURCEFILES 
	src/Plugin.cpp
	src/NanoGUIScreen.cpp
	src/NanoGUIInterface.cpp
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

set(DepName NanoGUILib)
set(${DepName}_CMAKE_ARGS -DNANOGUI_BUILD_SHARED=OFF -DNANOGUI_BUILD_PYTHON=OFF -DNANOGUI_BUILD_EXAMPLE=OFF -DCMAKE_C_FLAGS=-fPIC -DCMAKE_CXX_FLAGS=-fPIC)
set(${DepName}_GIT_REPOSITORY "https://github.com/wjakob/nanogui.git")
set(${DepName}_LIB_NAME nanogui)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)
include(${CMAKE_SOURCE_DIR}/third-party/OpenGL/OpenGL.cmake)
include(${CMAKE_SOURCE_DIR}/third-party/CPP11/CPP11.cmake)

include_directories(
	${dependency_dir}/${DepName}/build/install/include
	${dependency_dir}/${DepName}/src/ext/eigen
	${dependency_dir}/${DepName}/src/ext/glfw/include
	${dependency_dir}/${DepName}/src/ext/nanovg/src
)

#------------------------------------------
# Plugin
#------------------------------------------

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
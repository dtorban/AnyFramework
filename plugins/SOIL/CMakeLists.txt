#------------------------------------------
# Project
#------------------------------------------

project(SOIL)

set (SOURCEFILES 
	src/Plugin.cpp
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

set(DepName SOILLib)
set(${DepName}_URL "http://www.lonesock.net/files/soil.zip")
set(${DepName}_PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/patch/CMakeLists.txt ${dependency_dir}/${DepName}/src/CMakeLists.txt)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)


link_directories(${dependency_dir}/SOILLib/build/install/lib)

if(MSVC)
	set(ALL_LIBS ${ALL_LIBS} optimized SOILProject.lib debug SOILProjectd.lib)
else()
	set(ALL_LIBS ${ALL_LIBS} optimized libSOILProject.a debug libSOILProjectd.a)
endif()

# OpenGL
find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY})
set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
set(ALL_LIBS ${ALL_LIBS} ${OPENGL_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	find_library(COCOA_LIB Cocoa)
	find_library(IOKIT_LIB IOKit)
	find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    	find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
	set(ALL_LIBS ${ALL_LIBS} ${COCOA_LIB} ${IOKIT_LIB} ${CORE_FOUNDATION_FRAMEWORK} ${CORE_VIDEO_FRAMEWORK})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	find_package(Threads)
	find_package(X11)
	set(ALL_LIBS ${ALL_LIBS} ${CMAKE_THREAD_LIBS_INIT} rt Xrandr Xxf86vm Xi m dl ${X11_LIBRARIES})
endif()

include_directories(${dependency_dir}/SOILLib/build/install/include)

set(PROJECT_DEPS SOILLib)

#------------------------------------------
# Plugin
#------------------------------------------

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
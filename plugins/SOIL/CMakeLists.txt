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
set(${DepName}_LIB_NAME SOILProject)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)
include(${CMAKE_SOURCE_DIR}/third-party/OpenGL/OpenGL.cmake)

#------------------------------------------
# Plugin
#------------------------------------------

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
project(ExamplePlugin)

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

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
#------------------------------------------
# Download dependencies
#------------------------------------------

set(DepName RapidXMLLib)
set(${DepName}_GIT_REPOSITORY "https://github.com/dwd/rapidxml.git")
set(${DepName}_HEADER_ONLY True)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

#------------------------------------------
# Project
#------------------------------------------

project(RapidXML)

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
  ${dependency_dir}/RapidXMLLib/src
)

set(PROJECT_DEPS RapidXMLLib)

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
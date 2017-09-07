#------------------------------------------
# Download dependencies
#------------------------------------------

set(DepName RapidJSONLib)
set(${DepName}_GIT_REPOSITORY "https://github.com/miloyip/rapidjson.git")
set(${DepName}_HEADER_ONLY True)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

#------------------------------------------
# Project
#------------------------------------------

project(RapidJSON)

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
  ${dependency_dir}/RapidJSONLib/src/include
)

set(PROJECT_DEPS RapidJSONLib)

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
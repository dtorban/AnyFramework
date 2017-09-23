#------------------------------------------
# Project
#------------------------------------------

project(Assimp)

set (SOURCEFILES 
	src/Plugin.cpp
	src/AssetImporter.cpp
	src/AssimpScene.cpp
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

set(DepName AssimpLib)
set(${DepName}_GIT_REPOSITORY "https://github.com/assimp/assimp.git")
set(${DepName}_CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_SAMPLES=OFF -DASSIMP_ENABLE_BOOST_WORKAROUND=ON -DASSIMP_BUILD_TESTS=OFF)
set(${DepName}_LIB_NAME assimp)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

find_package(ZLIB)
if( NOT ZLIB_FOUND )
   ExternalProject_Get_Property(AssimpLib binary_dir)
   include_directories(${binary_dir}/contrib/zlib)
   link_directories(
   		${binary_dir}/contrib/zlib/Release
   		${binary_dir}/contrib/zlib/Debug
   )
   set(ZLIB_LIBRARIES optimized zlibstatic.lib debug zlibstaticd.lib)
   #set(ZLIB_LIBRARIES ${binary_dir}/contrib/zlib/Debug/zlibstaticd.lib)
endif(NOT ZLIB_FOUND)
set(ALL_LIBS ${ALL_LIBS} ${ZLIB_LIBRARIES})

set(DepName IrrXML)
set(${DepName}_URL "http://prdownloads.sourceforge.net/irrlicht/irrxml-1.2.zip")
set(${DepName}_HEADER_ONLY True)
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)
include_directories(${dependency_dir}/IrrXML/src/src)

set (SOURCEFILES 
	${SOURCEFILES}
	src/irrXMLProxy.cpp	
)

# Make into plugin
include(${CMAKE_SOURCE_DIR}/plugins/plugin.cmake)
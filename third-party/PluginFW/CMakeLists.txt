#------------------------------------------
# Download dependencies
#------------------------------------------

set(DepName PluginFW)

set(${DepName}_GIT_REPOSITORY "https://github.com/ivlab/PluginFramework.git")
set(${DepName}_GIT_TAG "v4")
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

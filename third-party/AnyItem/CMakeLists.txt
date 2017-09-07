#------------------------------------------
# Download dependencies
#------------------------------------------

set(DepName AnyItem)

#set(${DepName}_GIT_REPOSITORY "${PROJECT_SOURCE_DIR}/../AnyItem")
set(${DepName}_GIT_REPOSITORY "https://github.com/dtorban/AnyItem.git")
include(${CMAKE_SOURCE_DIR}/third-party/external.cmake)

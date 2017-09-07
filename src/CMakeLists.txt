project (AnyFramework)

# -------------------------------- Project -------------------------------------

include_directories(src)

# Core engine files

set (${PROJECT_NAME}_cpp
  plugin/IVPluginManager.cpp
  utilities/FileHelpers.cpp
  system/System.cpp

)
set (${PROJECT_NAME}_h

  core/
)

# Library configuration

set (${PROJECT_NAME}_source_files
  ${${PROJECT_NAME}_cpp}
)
set (${PROJECT_NAME}_header_files
${${PROJECT_NAME}_h}
)

source_group("Source Files" FILES ${${PROJECT_NAME}_cpp})
source_group("Header Files" FILES ${${PROJECT_NAME}_h})

add_library (${PROJECT_NAME} ${${PROJECT_NAME}_source_files} ${${PROJECT_NAME}_header_files})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})


install(DIRECTORY ${PROJECT_SOURCE_DIR}/  DESTINATION "include" FILES_MATCHING PATTERN "*.h")

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)




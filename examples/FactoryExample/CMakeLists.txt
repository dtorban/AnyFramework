project (FactoryExample)

# -------------------------------- Project -------------------------------------

message(${CMAKE_SOURCE_DIR}/src)

set (${PROJECT_NAME}_cpp
  src/main.cpp
)
set (${PROJECT_NAME}_h
)

# Library configuration

set (${PROJECT_NAME}_source_files
  ${${PROJECT_NAME}_cpp}
)

source_group("Header Files" FILES ${${PROJECT_NAME}_h})
source_group("Source Files" FILES ${${PROJECT_NAME}_cpp})

add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_source_files})
add_dependencies(${PROJECT_NAME} AnyItem PluginFW Spatialize)
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

#install( TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib
#         RUNTIME DESTINATION bin)




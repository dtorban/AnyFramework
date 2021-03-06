if (NOT TARGET ${DepName})
	set(${DepName}_checkout_Dir ${CMAKE_SOURCE_DIR}/third-party/${DepName}/src)
	make_directory(${${DepName}_checkout_Dir})
	include(ExternalProject)

	set(${DepName}_build_dir ${CMAKE_SOURCE_DIR}/third-party/${DepName}/build/${CMAKE_BUILD_TYPE})
	set(${DepName}_stamp_dir ${${DepName}_build_dir}/stamp)
	set(${DepName}_tmp_dir ${${DepName}_build_dir}/tmp)

	set(${DepName}_PREFIX "${${DepName}_checkout_Dir}")
	set(${DepName}_INSTALL_DIR "${${DepName}_build_dir}/../install")

	set(${DepName}_CMAKE_ARGS ${${DepName}_CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX=${${DepName}_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
	set(${DepName}_DIR "${${DepName}_INSTALL_DIR}")

	if (${DepName}_GIT_REPOSITORY)
		if (NOT ${DepName}_GIT_TAG)
			set(${DepName}_GIT_TAG "master")
		endif()
	
		if (${DepName}_HEADER_ONLY)
			ExternalProject_add(${DepName}
					PREFIX ${${DepName}_PREFIX}
					GIT_REPOSITORY "${${DepName}_GIT_REPOSITORY}"
					GIT_TAG ${${DepName}_GIT_TAG}
					INSTALL_DIR ${${DepName}_INSTALL_DIR}
					CMAKE_ARGS ${${DepName}_CMAKE_ARGS}
					UPDATE_COMMAND ""
					DOWNLOAD_DIR ${${DepName}_checkout_Dir}
					SOURCE_DIR ${${DepName}_checkout_Dir}
					TMP_DIR ${${DepName}_tmp_dir}
					STAMP_DIR ${${DepName}_stamp_dir}
					BINARY_DIR ${${DepName}_build_dir}
					PATCH_COMMAND "${${DepName}_PATCH_COMMAND}"
					BUILD_COMMAND ""
					CONFIGURE_COMMAND ""
					INSTALL_COMMAND ""
			)
		else()
			ExternalProject_add(${DepName}
					PREFIX ${${DepName}_PREFIX}
					GIT_REPOSITORY "${${DepName}_GIT_REPOSITORY}"
					GIT_TAG ${${DepName}_GIT_TAG}
					INSTALL_DIR ${${DepName}_INSTALL_DIR}
					CMAKE_ARGS ${${DepName}_CMAKE_ARGS}
					UPDATE_COMMAND ""
					DOWNLOAD_DIR ${${DepName}_checkout_Dir}
					SOURCE_DIR ${${DepName}_checkout_Dir}
					TMP_DIR ${${DepName}_tmp_dir}
					STAMP_DIR ${${DepName}_stamp_dir}
					BINARY_DIR ${${DepName}_build_dir}
					PATCH_COMMAND "${${DepName}_PATCH_COMMAND}"
			)

		endif()
	endif()

	if (${DepName}_URL)
	  get_filename_component(DepFileName ${${DepName}_URL} NAME)
	  set(DepFileName ${CMAKE_SOURCE_DIR}/third-party/repositories/${DepFileName})
		if (EXISTS ${DepFileName})
		  set(${DepName}_URL ${DepFileName})
		endif()
	  
		if (${DepName}_HEADER_ONLY)
			ExternalProject_add(${DepName}
					PREFIX ${${DepName}_PREFIX}
					URL "${${DepName}_URL}"
					INSTALL_DIR ${${DepName}_INSTALL_DIR}
					CMAKE_ARGS ${${DepName}_CMAKE_ARGS}
					UPDATE_COMMAND ""
					DOWNLOAD_DIR ${${DepName}_checkout_Dir}
					SOURCE_DIR ${${DepName}_checkout_Dir}
					TMP_DIR ${${DepName}_tmp_dir}
					STAMP_DIR ${${DepName}_stamp_dir}
					BINARY_DIR ${${DepName}_build_dir}
					PATCH_COMMAND "${${DepName}_PATCH_COMMAND}"
					BUILD_COMMAND ""
					CONFIGURE_COMMAND ""
					INSTALL_COMMAND ""
			)
		else()
			ExternalProject_add(${DepName}
					PREFIX ${${DepName}_PREFIX}
					URL "${${DepName}_URL}"
					INSTALL_DIR ${${DepName}_INSTALL_DIR}
					CMAKE_ARGS ${${DepName}_CMAKE_ARGS}
					UPDATE_COMMAND ""
					DOWNLOAD_DIR ${${DepName}_checkout_Dir}
					SOURCE_DIR ${${DepName}_checkout_Dir}
					TMP_DIR ${${DepName}_tmp_dir}
					STAMP_DIR ${${DepName}_stamp_dir}
					BINARY_DIR ${${DepName}_build_dir}
					PATCH_COMMAND "${${DepName}_PATCH_COMMAND}"
			)
		endif()
	endif()

	set_property(TARGET ${DepName} PROPERTY FOLDER "third-party")

	install(DIRECTORY ${${DepName}_INSTALL_DIR}/ DESTINATION "${CMAKE_INSTALL_PREFIX}/third-party/${DepName}")

	if (NOT ${DepName}_HEADER_ONLY)
		include_directories(${${DepName}_INSTALL_DIR}/include)
		link_directories(${${DepName}_INSTALL_DIR}/lib)

		if (${DepName}_LIB_NAME)
			set(lib_name ${${DepName}_LIB_NAME})
			if(MSVC)
				set(ALL_LIBS ${ALL_LIBS} optimized ${lib_name}.lib debug ${lib_name}d.lib)
			else()
				set(ALL_LIBS ${ALL_LIBS} optimized lib${lib_name}.a debug lib${lib_name}d.a)
			endif()
		endif()

	endif()

endif()

set(PROJECT_DEPS ${PROJECT_DEPS} ${DepName})

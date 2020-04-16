
#################################################################################
#   if WINDOWS && MSVC:	cmake -A x64 ..											#
#						cmake --build . --config Release						#
#																				#
#	if WINDOWS && MinGW: cmake ..												#
#						 mingw32-make											#
#																				#
#	if GNU: cmake ..															#
#			make																#
#################################################################################


cmake_minimum_required(VERSION 3.12)

project(backlight VERSION 1.0.0)

configure_file(config.h.in config.h)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
						PUBLIC 
						${OpenCV_INCLUDE_DIRS}
						${PROJECT_BINARY_DIR}
)


if(NOT MSVC)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

endif()


if(WIN32)


	if(MSVC)

find_file (OpenCV_LIB_DIR NAMES lib
			PATHS "$ENV{OpenCV_DIR}/x64"
			PATH_SUFFIXES "vc10" "vc11" "vc12" "vc14" "vc15" "vc16"
			NO_DEFAULT_PATH
)

target_link_directories(${PROJECT_NAME} PUBLIC ${OpenCV_LIB_DIR})


find_file (OpenCV_BIN_DIR NAMES bin
			PATHS "$ENV{OpenCV_DIR}/x64"
			PATH_SUFFIXES "vc10" "vc11" "vc12" "vc14" "vc15" "vc16"
			NO_DEFAULT_PATH
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	# DEBUG							# RELEASE
	debug opencv_imgproc420d.lib	optimized opencv_imgproc420.lib
	debug opencv_videoio420d.lib	optimized opencv_videoio420.lib
	debug opencv_highgui420d.lib 	optimized opencv_highgui420.lib
	debug 	 opencv_core420d.lib 	optimized 	 opencv_core420.lib
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:${OpenCV_BIN_DIR}/opencv_imgproc420d.dll>
		# RELEASE
		$<$<CONFIG:release>:${OpenCV_BIN_DIR}/opencv_imgproc420.dll> 
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:${OpenCV_BIN_DIR}/opencv_videoio420d.dll>
		# RELEASE
		$<$<CONFIG:release>:${OpenCV_BIN_DIR}/opencv_videoio420.dll> 
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:${OpenCV_BIN_DIR}/opencv_highgui420d.dll>
		# RELEASE
		$<$<CONFIG:release>:${OpenCV_BIN_DIR}/opencv_highgui420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:${OpenCV_BIN_DIR}/opencv_core420d.dll>
		# RELEASE
		$<$<CONFIG:release>:${OpenCV_BIN_DIR}/opencv_core420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:${OpenCV_BIN_DIR}/opencv_imgcodecs420d.dll>
		# RELEASE
		$<$<CONFIG:release>:${OpenCV_BIN_DIR}/opencv_imgcodecs420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>
)


	endif(MSVC)

	if(MINGW)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		$ENV{OpenCV_DIR}/x64/mingw/bin/libopencv_imgproc420.dll	${CMAKE_BINARY_DIR}
	
	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		$ENV{OpenCV_DIR}/x64/mingw/bin/libopencv_videoio420.dll	${CMAKE_BINARY_DIR}
		
	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		$ENV{OpenCV_DIR}/x64/mingw/bin/libopencv_highgui420.dll	${CMAKE_BINARY_DIR}

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		$ENV{OpenCV_DIR}/x64/mingw/bin/libopencv_core420.dll	${CMAKE_BINARY_DIR}

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		$ENV{OpenCV_DIR}/x64/mingw/bin/libopencv_imgcodecs420.dll ${CMAKE_BINARY_DIR}
)

	endif(MINGW)


endif(WIN32)
####################################################################################

include(CTest)

add_test("test_1d" ${CMAKE_BINARY_DIR}/Debug/${PROJECT_NAME})

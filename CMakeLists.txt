cmake_minimum_required(VERSION 3.12)

project(backlight)

add_executable(main main.cpp)
	
target_include_directories(main PUBLIC 
					$ENV{OPENCV_DIR}/include
)

target_link_directories(main PUBLIC 
					$ENV{OPENCV_DIR}/x64/vc15/lib
)


target_link_libraries(main PUBLIC
	# DEBUG							# RELEASE
	debug opencv_imgproc420d.lib	optimized opencv_imgproc420.lib
	debug opencv_videoio420d.lib	optimized opencv_videoio420.lib
	debug opencv_highgui420d.lib 	optimized opencv_highgui420.lib
	debug 	 opencv_core420d.lib 	optimized 	 opencv_core420.lib
)


add_custom_command(TARGET main POST_BUILD

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_imgproc420d.dll>
		# RELEASE
		$<$<CONFIG:release>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_imgproc420.dll> 
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_videoio420d.dll>
		# RELEASE
		$<$<CONFIG:release>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_videoio420.dll> 
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_highgui420d.dll>
		# RELEASE
		$<$<CONFIG:release>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_highgui420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_core420d.dll>
		# RELEASE
		$<$<CONFIG:release>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_core420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>

	COMMAND	${CMAKE_COMMAND} -E copy_if_different
		# DEBUG
		$<$<CONFIG:debug>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_imgcodecs420d.dll>
		# RELEASE
		$<$<CONFIG:release>:$ENV{OPENCV_DIR}/x64/vc15/bin/opencv_imgcodecs420.dll>
			# DEBUG
			$<$<CONFIG:debug>:${CMAKE_BINARY_DIR}/Debug>
			# RELEASE
			$<$<CONFIG:release>:${CMAKE_BINARY_DIR}/Release>
)
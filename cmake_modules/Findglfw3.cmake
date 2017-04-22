IF(WIN32)
	message(STATUS "Win32")
	FIND_PATH(GLFW3_INCLUDE_DIRS
		NAMES GLFW/glfw3.h
		PATHS
			$ENV{GLFW_ROOT}
			"c:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/"
		PATH_SUFFIXES include
		DOC "GLFW include directory"
		)
	FIND_LIBRARY(GLFW3_LIBRARY
		NAMES glfw3
		PATHS
			$ENV{GLFW_ROOT}
			"c:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/"
		PATH_SUFFIXES lib
		DOC "GLFW library directory"
		)
ELSE(WIN32)
	FIND_PATH(GLFW3_INCLUDE_DIRS
		NAMES GLFW/glfw3.h
		PATHS
			/usr/include
			/usr/local/include
		)
	FIND_LIBRARY(GLFW3_LIBRARY
		NAMES libGLFW.a GLFW libGLFW3.a GLFW3 libglfw.so libglfw.so.3 libglfw.so.3.0
		PATHS
			/usr/lib64
			/usr/lib
			/usr/local/lib64
			/usr/local/lib
		)
ENDIF(WIN32)

# message(STATUS "GLFW3 lib: ${GLFW3_LIBRARY}, include: ${GLFW3_INCLUDE_DIRS}")

IF(GLFW3_LIBRARY AND GLFW3_INCLUDE_DIRS)
	SET(GLFW3_FOUND TRUE)
	SET(GLFW_INCLUDE_DIRS ${GLFW3_INCLUDE_DIRS})
	SET(GLFW_LIBRARY_DIRS ${GLFW3_LIBRARY})
	message(STATUS "Found GLFW3: ${GLFW3_LIBRARY}")
ELSE()
	message(STATUS "GLFW3 NOT found!")
ENDIF(GLFW3_LIBRARY AND GLFW3_INCLUDE_DIRS)

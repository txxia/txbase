cmake_minimum_required (VERSION 3.2)

project(txbase C CXX)

#vscode-cmake-tools target debugging
include(CMakeToolsHelpers OPTIONAL)

set(CMAKE_VERBOSE_MAKEFILE 1)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
	add_definitions(/arch:SSE)
	add_definitions(/arch:SSE2)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -msse4.1")
endif()

# http://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
# if(MSVC)
#   # Force to always compile with W4
#   if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
#     string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#   else()
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#   endif()
# elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#   # Update if necessary
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# endif()

add_subdirectory(txbase)

enable_testing()
add_subdirectory(txbase_tests)

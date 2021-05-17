cmake_minimum_required(VERSION 3.19.1)
set(CMAKE_CXX_STANDARD 17)

project(pwutils VERSION 0.0.1 LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	include(GNUInstallDirs)
endif()

option(PWUTILS_STATIC "Build pwutils as static (ON) or shared library (OFF)" OFF)
if (NOT PWUTILS_STATIC)
    set(BUILD_SHARED_LIBS ON)
    message(STATUS "Building shared spida library")
	set(PWUTILS_LIBNAME "pwutils")
else()
    set(BUILD_SHARED_LIBS OFF)
    message(STATUS "Building static spida library")
	set(PWUTILS_LIBNAME "pwutils_static")
endif()

add_subdirectory(src)







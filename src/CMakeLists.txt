
cmake_minimum_required(VERSION 3.19)

set(SRC_FILES
	pwstats.cpp
	pwthreads.cpp
	pwstrings.cpp
	pwmath.cpp
	report/dat.cpp
	report/json.cpp
	report/vbreportbase.cpp
	report/reporthelper.cpp
	report/pwdir.cpp
	report/dataio.cpp
)

set(INCL_DIR "${pwutils_SOURCE_DIR}/include/pwutils")
set(INCLUDE_FILES
   "${INCL_DIR}/pwstats.h"
   "${INCL_DIR}/pwthreads.h"
   "${INCL_DIR}/pwexcept.h"
   "${INCL_DIR}/pwconstants.h"
   "${INCL_DIR}/pwstrings.h"
   "${INCL_DIR}/pwmath.h"
   "${INCL_DIR}/report/pwdir.h"
   "${INCL_DIR}/report/dat.hpp"
   "${INCL_DIR}/report/json.hpp"
   "${INCL_DIR}/report/vbreportbase.h"
   "${INCL_DIR}/report/reportbase.h"
   "${INCL_DIR}/report/reporthelper.h"
   "${INCL_DIR}/report/dataio.hpp"
)

add_library(${PWUTILS_LIBNAME} ${SRC_FILES} ${INCLUDE_FILES})
add_library("pw::${PWUTILS_LIBNAME}" ALIAS ${PWUTILS_LIBNAME})

target_include_directories(${PWUTILS_LIBNAME} PUBLIC 
	$<BUILD_INTERFACE:${pwutils_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/pwutils>
)

set_target_properties(${PWUTILS_LIBNAME} PROPERTIES
	VERSION ${pwutils_VERSION}
	SOVERSION 0
)

install(TARGETS ${PWUTILS_LIBNAME}
	EXPORT PWUtilsTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} 
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${INCL_DIR}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT PWUtilsTargets
	FILE PWUtilsTargets.cmake
	NAMESPACE pw::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pwutils
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
	${pwutils_SOURCE_DIR}/cmake/PWUtilsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/PWUtilsConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pwutils
	PATH_VARS CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/cmake/PWUtilsConfigVersion.cmake
	VERSION ${pwutils_VERSION}
	COMPATIBILITY AnyNewerVersion
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/PWUtilsConfig.cmake
				${CMAKE_CURRENT_BINARY_DIR}/cmake/PWUtilsConfigVersion.cmake
				DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pwutils
)




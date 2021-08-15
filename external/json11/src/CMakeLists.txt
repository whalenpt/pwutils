

cmake_minimum_required(VERSION 3.19)

set(INCL_DIR "${json11_SOURCE_DIR}/include/json11")
add_library(json11 json11.cpp ${INCL_DIR}/json11.hpp)
target_compile_options(json11
  PRIVATE -fPIC -fno-rtti -fno-exceptions -Wall)

target_include_directories(json11 PRIVATE
	$<BUILD_INTERFACE:${json11_SOURCE_DIR}/include/json11>
	$<INSTALL_INTERFACE:include/json11>
)

target_include_directories(json11 PUBLIC 
	$<BUILD_INTERFACE:${json11_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)



# Set warning flags, which may vary per platform

install(TARGETS json11 
	EXPORT JsonTargets
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib 
	RUNTIME DESTINATION bin
)
install(DIRECTORY ${INCL_DIR}
	DESTINATION include
)
install(EXPORT JsonTargets
	FILE JsonTargets.cmake
	DESTINATION lib/cmake/json11
)
configure_file("${json11_SOURCE_DIR}/cmake/json11.pc.in"
    "json11.pc" @ONLY
)
install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/json11.pc"
    DESTINATION lib/cmake/json11
)



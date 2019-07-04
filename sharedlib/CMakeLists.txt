option(BUILD_DLL "Build as shared library" ON)

set(_SOURCES "")
list(APPEND _SOURCES "sharedlib.cpp")

set(SHAREDLIB sharedlib)

set(LIB_DLL 0)

if(BUILD_DLL)
	set(LIB_DLL 1)
	add_library(${SHAREDLIB} SHARED ${_SOURCES})
	target_compile_definitions(${SHAREDLIB} PRIVATE "-DLIB_BUILD_DLL")
else()
	add_library(${SHAREDLIB} STATIC ${_SOURCES})
endif()

set_target_properties(${SHAREDLIB}
	PROPERTIES
	LIBRARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib"
	ARCHIVE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib"
)

configure_file("config.h.in" "${CMAKE_BINARY_DIR}/include/config.h")
target_include_directories(${SHAREDLIB} PUBLIC "${CMAKE_BINARY_DIR}/include")
set(SHAREDLIB ${SHAREDLIB} PARENT_SCOPE)
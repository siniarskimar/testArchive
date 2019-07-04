add_library(dll SHARED "test.cpp")

target_compile_definitions(dll PUBLIC "TEST_BUILD_DLL")

add_executable(cpp "main.cpp")

set_target_properties(cpp
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_property(TARGET cpp PROPERTY CXX_STANDARD 14)

target_link_libraries(cpp dll)

#add_custom_command(TARGET cpp POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res $<TARGET_FILE_DIR:cpp>/quizzes
#)
cmake_minimum_required(VERSION 3.14.0)

project(Tempest 
		VERSION 0.0.0
		LANGUAGES CXX
		DESCRIPTION "Graphics Engine")
		
#Sets ups the module path to work with the a custom on so the defualt CMake modules work.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}../../../glew-2.1.0/")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Tempest src/main.cpp)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tempest)

target_link_libraries(Tempest PRIVATE OpenGL::GL OpenGL::GLU GLEW::GLEW)
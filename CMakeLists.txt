cmake_minimum_required(VERSION 3.14.0)

project(Tempest 
        VERSION 0.0.0
        LANGUAGES CXX
        DESCRIPTION "Tempest Engine")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Sets ups the module path to work with the a custom on so the defualt CMake modules work.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}../../../glew-2.1.0/")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src/Tempest)

add_executable(Game src/Game.cpp)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

if(WIN32)
    add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_BINARY_DIR}/src/Tempest/Debug/Tempest.dll"
            $<TARGET_FILE_DIR:Game>)
endif()


target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Tempest/Public)

target_link_libraries(Game PRIVATE OpenGL::GL OpenGL::GLU GLEW::GLEW Tempest)


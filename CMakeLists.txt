cmake_minimum_required(VERSION 3.19.0)

project(Tempest 
        VERSION 0.0.0
        LANGUAGES CXX
        DESCRIPTION "Tempest Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Tempest)

add_executable(Game src/Game.cpp)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

if(WIN32)
    add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${PROJECT_BINARY_DIR}/src/Tempest/Debug/Tempest.dll"
            $<TARGET_FILE_DIR:Game>)
endif()

target_link_libraries(Game PRIVATE Tempest)


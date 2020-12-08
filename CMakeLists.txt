cmake_minimum_required(VERSION 3.19.0)

project(Tempest 
        VERSION 0.1.0
        LANGUAGES CXX C
        DESCRIPTION "Tempest Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Tempest)

add_executable(Game src/Game.cpp)

set_property(TARGET Game PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(Game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
    set_property(
        TARGET Game
        APPEND
        PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
    )

target_link_libraries(Game PRIVATE Tempest)


cmake_minimum_required(VERSION 3.19.0)

project(Tempest 
        VERSION 0.1.2
        LANGUAGES CXX C
        DESCRIPTION "Tempest Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GAME_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/GameSrc/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameSrc/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameSrc/*.glsl"
)

set(TEMPEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/EngineSrc/Tempest")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GAME_SOURCE})

add_subdirectory(EngineSrc/Tempest)

add_executable(Game ${GAME_SOURCE})

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

#Using a bit of post-processing we can select the varaiables we need to
#get the correct version of the share library after compiling it.
#As we have already built the Game target it will know where to copy it to.
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/GameSrc/Resources"
        $<TARGET_FILE_DIR:Game>)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/GameSrc/Resources"
        ${PROJECT_BINARY_DIR})

target_include_directories(Game PUBLIC ${TEMPEST_INCLUDE_DIR})
target_link_libraries(Game PRIVATE Tempest)


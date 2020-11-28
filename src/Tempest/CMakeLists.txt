
include(GenerateExportHeader)

file(GLOB_RECURSE TEMPEST_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/Tempest/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Tempest/*.h"
)

if(MSVC)
    set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../loggingLibrary/spdlog/include")
    set(SPDLOG_LIBRARIES "${CMAKE_SOURCE_DIR}../../../loggingLibrary/logStaticLib/spdlog.lib")
    set(GLEW_USE_STATIC_LIBS True)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEMPEST_SOURCE})
endif()

#Sets ups the module path to work with the a custom on so the defualt CMake modules work.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}../../../glew-2.1.0/")

set(GLFW_LOCATION "${CMAKE_SOURCE_DIR}../../../glfw-3.3.2")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)

add_library(Tempest SHARED ${TEMPEST_SOURCE})

set(PRECOMPILED_HEADER Tempest/PublicInclude)

target_precompile_headers(Tempest PUBLIC "${PRECOMPILED_HEADER}/PreComp.h")

generate_export_header(Tempest)

target_include_directories(Tempest PUBLIC ${PROJECT_BINARY_DIR}/src/Tempest ${SPDLOG_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${PRECOMPILED_HEADER})
target_link_libraries(Tempest PRIVATE OpenGL::GL OpenGL::GLU ${GLEW_STATIC_LIBRARIES} ${SPDLOG_LIBRARIES} ${GLFW_LIBRARIES}) 
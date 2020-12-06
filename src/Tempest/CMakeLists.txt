
file(GLOB_RECURSE TEMPEST_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/Tempest/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Tempest/*.h"
)

if(MSVC)
    set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../loggingLibrary/spdlog/include")
    set(SPDLOG_LIBRARIES "${CMAKE_SOURCE_DIR}../../../loggingLibrary/logStaticLib/spdlog.lib")
    set(GML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../glm-master")
    #set(GLEW_USE_STATIC_LIBS True)
    set(IMGUI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/imgui")
    set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/glew-2.1.0/include")
    set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/glfw/include")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEMPEST_SOURCE})
endif()

#Sets ups the module path to work with the a custom on so the defualt CMake modules work.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

add_subdirectory(vender/glew-2.1.0)
add_subdirectory(vender/imgui)
add_subdirectory(vender/glfw)

add_library(Tempest STATIC ${TEMPEST_SOURCE})

set_property(TARGET Tempest PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    set_property(
        TARGET Tempest
        APPEND
        PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
    )

set(PRECOMPILED_HEADER Tempest/PublicInclude)
target_precompile_headers(Tempest PUBLIC "${PRECOMPILED_HEADER}/PreComp.h")

target_include_directories(Tempest PUBLIC ${PROJECT_BINARY_DIR}/src/Tempest ${SPDLOG_INCLUDE_DIR} ${PRECOMPILED_HEADER} ${IMGUI_INCLUDE_DIR} ${GML_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
target_link_libraries(Tempest PRIVATE  ${SPDLOG_LIBRARIES} IMGUI GLEW GLFW) 
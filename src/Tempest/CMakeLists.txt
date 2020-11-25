
set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../loggingLibrary/spdlog/include")
set(SPDLOG_LIBRARIES "${CMAKE_SOURCE_DIR}../../../loggingLibrary/logStaticLib/spdlog.lib")

include(GenerateExportHeader)

file(GLOB_RECURSE TEMPEST_MAIN
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB_RECURSE TEMPEST_EVENTS
    "${CMAKE_CURRENT_SOURCE_DIR}/Events/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Events/*.h"
)

file(GLOB_RECURSE TEMPEST_PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h"
)

add_library(Tempest SHARED ${TEMPEST_MAIN} ${TEMPEST_EVENTS} ${TEMPEST_PUBLIC})

source_group("Event"  FILES ${TEMPEST_EVENTS})
source_group("Public" FILES ${TEMPEST_PUBLIC})

generate_export_header(Tempest)

target_include_directories(Tempest PUBLIC ${PROJECT_BINARY_DIR}/src/Tempest ${SPDLOG_INCLUDE_DIR})
target_link_libraries(Tempest PUBLIC ${SPDLOG_LIBRARIES})
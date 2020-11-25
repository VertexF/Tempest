
set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../loggingLibrary/spdlog/include")
set(SPDLOG_LIBRARIES "${CMAKE_SOURCE_DIR}../../../loggingLibrary/logStaticLib/spdlog.lib")

include(GenerateExportHeader)
add_library(Tempest SHARED Application.cpp Application.h
                           Log.cpp Log.h
                           EntryPoint.h
                           Core.h
                           Public/Tempest.h)

generate_export_header(Tempest)

target_include_directories(Tempest PUBLIC ${PROJECT_BINARY_DIR}/src/Tempest ${SPDLOG_INCLUDE_DIR})
target_link_libraries(Tempest PUBLIC ${SPDLOG_LIBRARIES})
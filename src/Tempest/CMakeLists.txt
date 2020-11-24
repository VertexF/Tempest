include(GenerateExportHeader)
add_library(Tempest SHARED Application.cpp Application.h
                           EntryPoint.h
						   Core.h
                           Public/Tempest.h)

generate_export_header(Tempest)
target_include_directories(Tempest PUBLIC ${PROJECT_BINARY_DIR}/src/Tempest)
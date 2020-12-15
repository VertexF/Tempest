add_library(STB STATIC stb_image.h stb_image.cpp)

set_property(TARGET STB PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

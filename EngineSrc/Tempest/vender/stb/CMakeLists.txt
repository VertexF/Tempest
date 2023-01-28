add_library(STB STATIC stb_image.h stb_image.cpp stb_truetype.h)

if(MSVC)
    set_property(TARGET STB PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
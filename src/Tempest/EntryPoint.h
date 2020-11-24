#ifndef ENTRY_POINT_HDR
#define ENTRY_POINT_HDR

#include "Application.h"

#ifdef WIN32

extern Tempest::Application* Tempest::createApplication();

int main(int argc, char** argv) 
{
    auto app = Tempest::createApplication();
    app->run();
    delete app;
    return 0;
}

#endif

#endif // !ENTRY_POINT_HDR

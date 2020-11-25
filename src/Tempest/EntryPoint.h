#ifndef ENTRY_POINT_HDR
#define ENTRY_POINT_HDR

#include "Application.h"
#include "Log.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

#ifdef WIN32

extern Tempest::Application* Tempest::createApplication();

int main(int argc, char** argv) 
{
    Tempest::Log::init();
    TEMPEST_ERROR("Hello Leon! ");
    TEMPEST_WARN("We now");
    TEMPEST_INFO("have a");
    TEMPEST_TRACE("logging system!");

    auto app = Tempest::createApplication();
    app->run();
    delete app;
    return 0;
}

#endif

#endif // !ENTRY_POINT_HDR

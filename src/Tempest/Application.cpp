#include "Application.h"

#include <iostream>

#include "Log.h"
#include "Events/ApplicationEvents.h"

namespace Tempest
{
    Application::Application() 
    {
    
    }

    Application::~Application()
    {
    
    }

    void Application::run()
    {
        WindowResizeEvent winEvent(1280, 790);
        TEMPEST_INFO(winEvent);
    }
}
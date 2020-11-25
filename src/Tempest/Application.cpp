#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

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

        PressedKeyEvent pressKey(2, 1);
        TEMPEST_TRACE(pressKey);

        MouseMovedEvent moved(2.f, 1.f);
        TEMPEST_ERROR(moved);
    }
}
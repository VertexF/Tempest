#include "Application.h"

#include "PreComp.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

#include <glfw/glfw3.h>

namespace Tempest
{
    Application::Application() 
    {
        _window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application()
    {
    
    }

    void Application::run()
    {
        bool running = true;

        while (running)
        {
            glClearColor(0.f, 1.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            _window->onUpdate();
        }
    }
}
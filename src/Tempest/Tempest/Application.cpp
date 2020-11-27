#include "Application.h"

#include "PreComp.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/Event.h"
#include "Layer.h"

#include <glfw/glfw3.h>

namespace Tempest
{
    Application::Application() 
    {
        _window = std::unique_ptr<Window>(Window::create());
        _window->setCallbackFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
    
    }

    void Application::onEvent(Event &e) 
    {
        EventDispatcher eventDispatcher(e);
        eventDispatcher.dispatch<WindowClosedEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));

        TEMPEST_TRACE("Tempest Event: {0}", e);

        //This is meant to go in reserve to handle events like keypresses.
        for (auto it = _layerStack.end(); it != _layerStack.begin();) 
        {
            (*--it)->onEvent(e);
            if (e.isHandled)
            {
                break;
            }
        }
    }

    void Application::run()
    {
        _running = true;
        while (_running)
        {
            glClearColor(0.f, 1.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer *layer : _layerStack)
            {
                layer->onUpdate();
            }

            _window->onUpdate();
        }
    }

    bool Application::onWindowClosed(WindowClosedEvent &closed)
    {
        _running = false;
        return true;
    }

    void Application::pushLayer(Layer *layer)
    {
        _layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *layer)
    {
        _layerStack.pushOverlay(layer);
    }
}
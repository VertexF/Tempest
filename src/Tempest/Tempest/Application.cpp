#include "Application.h"

#include "PreComp.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/Event.h"
#include "Layer.h"
#include "Input.h"

#include <glfw/glfw3.h>

namespace Tempest
{
    Application *Application::_instance = nullptr;

    //First we intialise the window which sets up all the stuff needed to run.
    //Then we set up callback functions to the on event function in this class.
    //This allows events to be sent GLFW from our onEvent function.
    Application::Application() 
    {
        _instance = this;

        _window = std::unique_ptr<Window>(Window::create());
        _window->setCallbackFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
    }

    //The only event we need to dispatch is our windows close event.
    //This sends out a signal, that goes through the dispatcher and gets handled
    //by running the WindowClosedEvent function as a callback.
    void Application::onEvent(Event &e) 
    {
        EventDispatcher eventDispatcher(e);
        eventDispatcher.dispatch<WindowClosedEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));

        //TEMPEST_TRACE("Tempest Event: {0}", e);

        //This is meant to go in reserve to handle events like keypresses.
        for (auto it = _layerStack.end(); it != _layerStack.begin();) 
        {
            (*--it)->onEvent(e);
            //When the event is handled we don't need to continue looping
            //through the layer stack.
            if (e.isHandled)
            {
                break;
            }
        }
    }

    //The main loop function. Every layer need to be updated in order so we 
    //render layers on top of each other correctly.
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

    //This is what actually gets ran in the event dispatcher when the signal 
    //is sent on the event of a closed window.
    bool Application::onWindowClosed(WindowClosedEvent &closed)
    {
        _running = false;
        return true;
    }

    void Application::pushLayer(Layer *layer)
    {
        _layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer *layer)
    {
        _layerStack.pushOverlay(layer);
        layer->onAttach();
    }
}
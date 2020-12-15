#include "Application.h"

#include "PreComp.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/Event.h"
#include "Layer.h"
#include "Input.h"

#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererCommands.h"

#include <GLFW/glfw3.h>

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

        Renderer::init();

        _imGuiLayer = new ImGuiLayer();
        pushOverlay(_imGuiLayer);
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

        //This is meant to go in reserve to handle events like keypresses.
        for (auto it = _layerStack.rbegin(); it != _layerStack.rend(); ++it) 
        {
            //When the event is handled we don't need to continue looping
            //through the layer stack.
            if (e.isHandled)
            {
                break;
            }

            (*it)->onEvent(e);
        }
    }

    //The main loop function. Every layer need to be updated in order so we 
    //render layers on top of each other correctly.
    void Application::run()
    {
        _running = true;
        while (_running)
        {
            float time = static_cast<float>(glfwGetTime());
            TimeStep timestep(time - _lastFrameTime);
            _lastFrameTime = time;

            for(Layer *layer : _layerStack)
            {
                layer->onUpdate(timestep);
            }

            _imGuiLayer->begin();
            for (Layer* layer : _layerStack)
            {
                layer->onImGuiRender();
            }
            _imGuiLayer->end();

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
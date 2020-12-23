#include "Application.h"

#include "PreComp.h"
#include "Tempest/Events/ApplicationEvents.h"
#include "Tempest/Events/KeyEvents.h"
#include "Tempest/Events/MouseEvents.h"
#include "Tempest/Events/Event.h"
#include "Layer.h"
#include "Input.h"

#include "Tempest/Renderer/Shader.h"
#include "Tempest/Platform/OpenGL/OpenGLBuffer.h"
#include "Tempest/Renderer/Renderer.h"
#include "Tempest/Renderer/RendererCommands.h"

#include <GLFW/glfw3.h>

namespace Tempest
{
    Application *Application::_instance = nullptr;

    //First we intialise the window which sets up all the stuff needed to run.
    //Then we set up callback functions to the on event function in this class.
    //This allows events to be sent GLFW from our onEvent function.
    Application::Application()
    {
        TEMPEST_PROFILE_FUNCTION();

        _instance = this;

        _window = Window::create();
        _window->setCallbackFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));

        Renderer::init();

        _imGuiLayer = new ImGuiLayer();
        pushOverlay(_imGuiLayer);
    }

    Application::~Application()
    {
        TEMPEST_PROFILE_FUNCTION();

        Renderer::shutdown();
    }

    //The only event we need to dispatch is our windows close event.
    //This sends out a signal, that goes through the dispatcher and gets handled
    //by running the WindowClosedEvent function as a callback.
    void Application::onEvent(Event &e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        EventDispatcher eventDispatcher(e);
        eventDispatcher.dispatch<WindowClosedEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
        eventDispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));

        //This is meant to go in reserve to handle events like keypresses.
        for (auto it = _layerStack.rbegin(); it != _layerStack.rend(); it++) 
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
        TEMPEST_PROFILE_FUNCTION();

        _running = true;
        while (_running)
        {
            TEMPEST_PROFILE_SCOPE("Main run loop");

            float time = static_cast<float>(glfwGetTime());
            TimeStep timestep(time - _lastFrameTime);
            _lastFrameTime = time;

            if (_minimized == false)
            {
                {
                    TEMPEST_PROFILE_SCOPE("Layer stack update");
                    for (Layer* layer : _layerStack)
                    {
                        layer->onUpdate(timestep);
                    }
                }
            }

            _imGuiLayer->begin();
            {
                TEMPEST_PROFILE_FUNCTION("Layer stack ImGui Update");
                for (Layer* layer : _layerStack)
                {
                    layer->onImGuiRender();
                }
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

    bool Application::onWindowResize(WindowResizeEvent& resized)
    {
        TEMPEST_PROFILE_FUNCTION();

        if (resized.getWidth() == 0 || resized.getHeight() == 0) 
        {
            _minimized = true;
            return false;
        }

        Renderer::onResizeEvent(resized.getWidth(), resized.getHeight());

        _minimized = false;
        return false;
    }

    void Application::pushLayer(Layer *layer)
    {
        TEMPEST_PROFILE_FUNCTION();

        _layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *layer)
    {
        TEMPEST_PROFILE_FUNCTION();

        _layerStack.pushOverlay(layer);
    }
}
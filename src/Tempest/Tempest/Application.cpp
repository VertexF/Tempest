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

#include <gl/glew.h>

#include <glfw/glfw3.h>
#include "imgui.h"

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

        
        _imGuiLayer = new ImGuiLayer();
        pushOverlay(_imGuiLayer);

        glGenVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        _vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = {0, 1, 2};
        _indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSource = R"(
            #version 330 core
            
            layout(location = 0) in vec3 position;
            out vec3 v_position;
            
            void main()
            {
                v_position = position;
                gl_Position = vec4(position, 1.0);
            }
        )";

        std::string fragmentSource = R"(
            #version 330 core
            
            layout(location = 0) out vec4 colour;
            in vec3 v_position;
            
            void main()
            {
                colour = vec4(v_position * 0.5 + 0.5, 1.0);
            }
        )";

        _shader = std::make_unique<Shader>(vertexSource, fragmentSource);
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
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.f);

            _shader->bind();
            //_vertexBuffer->bind();
            //_indexBuffer->bind();
            glBindVertexArray(_vertexArray);
            glDrawElements(GL_TRIANGLES, _indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            for(Layer *layer : _layerStack)
            {
                layer->onUpdate();
            }

            _imGuiLayer->begin();
            for (Layer* layer : _layerStack)
            {
                _imGuiLayer->onImGuiRender();
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
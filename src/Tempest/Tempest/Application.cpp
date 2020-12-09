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

namespace Tempest
{
    Application *Application::_instance = nullptr;

    //First we intialise the window which sets up all the stuff needed to run.
    //Then we set up callback functions to the on event function in this class.
    //This allows events to be sent GLFW from our onEvent function.
    Application::Application() :
        _camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        _instance = this;

        _window = std::unique_ptr<Window>(Window::create());
        _window->setCallbackFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));

        _imGuiLayer = new ImGuiLayer();
        pushOverlay(_imGuiLayer);

        _vertexArray.reset(VertexArray::create());
        _squareVA.reset(VertexArray::create());

        float vertices[3 * 7] =
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        float vertices2[3 * 4] =
        {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
             -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(vertices2, sizeof(vertices2)));

        BufferLayout layout = {
            { ShaderDataType::FLOAT3, "position" },
            { ShaderDataType::FLOAT4, "inColour" }
        };

        BufferLayout layoutSquare = {
            { ShaderDataType::FLOAT3, "position" }
        };

        vertexBuffer->setLayout(layout);
        squareVB->setLayout(layoutSquare);

        _vertexArray->addVertexBuffer(vertexBuffer);
        _squareVA->addVertexBuffer(squareVB);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        _vertexArray->setIndexBuffer(indexBuffer);

        uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t)));
        _squareVA->setIndexBuffer(squareIB);

        std::string vertexSource = R"(
            #version 330 core
            
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 inColour;

            uniform mat4 uViewProjectmatrix;

            out vec3 _position;
            out vec4 _colour;
            
            void main()
            {
                _colour = inColour;
                _position = position;
                gl_Position = uViewProjectmatrix * vec4(_position, 1.0);
            }
        )";

        std::string fragmentSource = R"(
            #version 330 core
            
            layout(location = 0) out vec4 colour;
            in vec3 _position;
            in vec4 _colour;
            
            void main()
            {
                colour = vec4(_position * 0.5 + 0.5, 1.0);
                colour = _colour;
            }
        )";

        _shader = std::make_unique<Shader>(vertexSource, fragmentSource);

        std::string vertexSource2 = R"(
            #version 330 core
            
            layout(location = 0) in vec3 position;

            uniform mat4 uViewProjectmatrix;

            out vec3 _position;
            
            void main()
            {
                _position = position;
                gl_Position = uViewProjectmatrix * vec4(_position, 1.0);
            }
        )";

        std::string fragmentSource2 = R"(
            #version 330 core
            
            layout(location = 0) out vec4 colour;
            in vec3 _position;
            
            void main()
            {
                colour = vec4(0.2f, 0.3f, 0.8f, 1.0f);
            }
        )";

        _squareShader = std::make_unique<Shader>(vertexSource2, fragmentSource2);
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
            RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
            RendererCommands::clear();
            
            Renderer::beginScene(_camera);

            _camera.setPosition({-0.5f, 0.5f, 0.f});
            _camera.setRotation(-90.f);

            Renderer::submit(_squareVA, _squareShader);
            Renderer::submit(_vertexArray, _shader);

            Renderer::endScene();

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
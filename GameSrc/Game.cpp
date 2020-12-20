#include <iostream>
#include <Tempest.h>

#include "Tempest/Core/EntryPoint.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Tempest/Platform/OpenGL/OpenGLShader.h"
#include "Tempest/Renderer/Shader.h"

#include "Game2D.h"

//The client also create it own layers depending on what it needs.
class ExampleLayer : public Tempest::Layer 
{
public:
    ExampleLayer() : Layer("Example Layer"),
        _cameraController(1280.f / 720.f), _playerPosition(0.f), _squareColour({0.8f, 0.3f, 0.2f})
    {
        _vertexArray = Tempest::VertexArray::create();
        _squareVA = Tempest::VertexArray::create();

        float vertices[3 * 7] =
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        float vertices2[5 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 0.f, 0.f,
             0.5f, -0.5f, 0.0f, 1.f, 0.f,
             0.5f,  0.5f, 0.0f, 1.f, 1.f,
            -0.5f,  0.5f, 0.0f, 0.f, 1.f
        };

        Tempest::ref<Tempest::VertexBuffer> vertexBuffer;
        vertexBuffer = Tempest::VertexBuffer::create(vertices, sizeof(vertices));
        Tempest::ref<Tempest::VertexBuffer> squareVB;
        squareVB = Tempest::VertexBuffer::create(vertices2, sizeof(vertices2));

        Tempest::BufferLayout layout = {
            { Tempest::ShaderDataType::FLOAT3, "position" },
            { Tempest::ShaderDataType::FLOAT4, "inColour" }
        };

        Tempest::BufferLayout layoutSquare = {
            { Tempest::ShaderDataType::FLOAT3, "position" },
            { Tempest::ShaderDataType::FLOAT2, "texCoord" }
        };

        vertexBuffer->setLayout(layout);
        squareVB->setLayout(layoutSquare);

        _vertexArray->addVertexBuffer(vertexBuffer);
        _squareVA->addVertexBuffer(squareVB);

        uint32_t indices[3] = { 0, 1, 2 };
        Tempest::ref<Tempest::IndexBuffer> indexBuffer;
        indexBuffer = Tempest::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
        _vertexArray->setIndexBuffer(indexBuffer);

        uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
        Tempest::ref<Tempest::IndexBuffer> squareIB;
        squareIB = Tempest::IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
        _squareVA->setIndexBuffer(squareIB);

        _shader = Tempest::Shader::create("Assets/Shaders/Triangle.glsl");
        _squareShader = Tempest::Shader::create("Assets/Shaders/FlatColour.glsl");
        auto textureShader = _shaderLibrary.load("Assets/Shaders/Texture.glsl");

        _characterTexture = Tempest::Texture2D::create("Assets/Textures/alpha.png"); 

        std::dynamic_pointer_cast<Tempest::OpenGLShader>(textureShader)->bind();
        std::dynamic_pointer_cast<Tempest::OpenGLShader>(textureShader)->setIntUniform("uTexture", 0);
    }

    virtual void onUpdate(Tempest::TimeStep timeStep) override
    {
        _cameraController.onUpdate(timeStep);
        _playerPosition = _cameraController.getCameraPosition();

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        Tempest::Renderer::beginScene(_cameraController.getCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->bind();
        std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->setVec3Uniform("uColour", _squareColour);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Tempest::Renderer::submit(_squareVA, _squareShader, squareTransform);
            }
        }

        auto textureShader = _shaderLibrary.get("Texture");

        _characterTexture->bind();
        glm::mat4 tryTransform = glm::translate(glm::mat4(1.0f), _playerPosition) * scale;
        Tempest::Renderer::submit(_squareVA, textureShader, tryTransform);

        Tempest::Renderer::endScene();
    }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Settings");

        ImGui::ColorEdit3("Square Colour Picker", glm::value_ptr(_squareColour));

        ImGui::End();
    }

    virtual void onEvent(Tempest::Event &e) override
    {
        _cameraController.onEvent(e);
    }
private:
    //OpenGL stuff
    Tempest::ref<Tempest::Shader> _shader;
    Tempest::ref<Tempest::Shader> _squareShader;

    Tempest::ref<Tempest::VertexArray> _vertexArray;
    Tempest::ref<Tempest::VertexArray> _squareVA;

    Tempest::ref<Tempest::Texture2D> _characterTexture;

    Tempest::OrthographicalCameraController _cameraController;

    Tempest::ShaderLibrary _shaderLibrary;

    glm::vec3 _playerPosition;

    glm::vec3 _squareColour;
};

//The client uses the application as a template to create the game.
class Game : public Tempest::Application
{
public:
    Game() 
    {
        //pushLayer(new ExampleLayer());
        pushLayer(new Game2D());
    }

    ~Game() {}
};

//We kick start the engine by using our client class that is 
//inherited from the the engine.
Tempest::Application* Tempest::createApplication() 
{
    return new Game();
}
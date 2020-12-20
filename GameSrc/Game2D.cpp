#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tempest/Platform/OpenGL/OpenGLShader.h"
#include "Tempest/Renderer/Shader.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

Game2D::Game2D() : Layer("Game"), _cameraController(1280.f / 720.f), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f})
{

}

void Game2D::onAttach() 
{
    _squareVA = Tempest::VertexArray::create();

    float squareVerts[5 * 4] =
    {
        -0.5f, -0.5f, 0.0f, 0.f, 0.f,
         0.5f, -0.5f, 0.0f, 1.f, 0.f,
         0.5f,  0.5f, 0.0f, 1.f, 1.f,
        -0.5f,  0.5f, 0.0f, 0.f, 1.f
    };

    Tempest::ref<Tempest::VertexBuffer> squareVB;
    squareVB = Tempest::VertexBuffer::create(squareVerts, sizeof(squareVerts));


    Tempest::BufferLayout layoutSquare = {
        { Tempest::ShaderDataType::FLOAT3, "position" },
        { Tempest::ShaderDataType::FLOAT2, "texCoord" }
    };

    squareVB->setLayout(layoutSquare);
    _squareVA->addVertexBuffer(squareVB);

    uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
    Tempest::ref<Tempest::IndexBuffer> squareIB;
    squareIB = Tempest::IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
    _squareVA->setIndexBuffer(squareIB);

    _squareShader = Tempest::Shader::create("Assets/Shaders/FlatColour.glsl");
}

void Game2D::onDetach() 
{
}

void Game2D::onUpdate(Tempest::TimeStep timeStep) 
{
    _cameraController.onUpdate(timeStep);

    Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer::beginScene(_cameraController.getCamera());

    std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->bind();
    std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->setVec4Uniform("uColour", _squareColour);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Tempest::Renderer::submit(_squareVA, _squareShader, squareTransform);
        }
    }

    Tempest::Renderer::endScene();
}

void Game2D::onEvent(Tempest::Event& e)
{
    _cameraController.onEvent(e);
}

void Game2D::onImGuiRender() 
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

    ImGui::End();
}

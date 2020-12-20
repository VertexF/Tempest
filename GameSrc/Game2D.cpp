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

}

void Game2D::onDetach() 
{
}

void Game2D::onUpdate(Tempest::TimeStep timeStep) 
{
    _cameraController.onUpdate(timeStep);

    Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer2D::beginScene(_cameraController.getCamera());

    Tempest::Renderer2D::drawQuad({ 0.f, 0.f }, {1.f, 1.f}, _squareColour);

    Tempest::Renderer2D::endScene();

    //std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->bind();
    //std::dynamic_pointer_cast<Tempest::OpenGLShader>(_squareShader)->setVec4Uniform("uColour", _squareColour);
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

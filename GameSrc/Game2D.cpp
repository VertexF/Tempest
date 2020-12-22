#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

Game2D::Game2D() : Layer("Game"), _cameraController(1280.f / 720.f), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f})
{
}

void Game2D::onAttach() 
{
    _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/Checkerboard.png");
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
    Tempest::Renderer2D::drawQuad({ 3.f, -1.f }, { 0.5f, 2.f }, { 0.2f, 0.3f, 0.8f, 1.f });
    Tempest::Renderer2D::drawQuad({ 0.f, 0.f -0.1f }, { 10.f, 10.f }, _backgroundTexture);

    Tempest::Renderer2D::endScene();
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

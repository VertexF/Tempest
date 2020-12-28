#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
{
    _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);
}

void Game2D::onAttach()
{
    TEMPEST_PROFILE_FUNCTION();

    _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/Checkerboard.png");
}

void Game2D::onDetach()
{
    TEMPEST_PROFILE_FUNCTION();
}

void Game2D::onUpdate(Tempest::TimeStep timeStep)
{
    TEMPEST_PROFILE_FUNCTION();

    _cameraController->onUpdate(timeStep);

    Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer2D::beginScene(_cameraController->getCamera());

    //Tempest::Renderer2D::drawRotatedQuad({ 0.f, 0.f }, { 1.f, 1.f }, glm::radians(30.f), _squareColour);
    Tempest::Renderer2D::drawQuad({ 0.f, 0.f }, { 1.f, 1.f }, _squareColour);
    Tempest::Renderer2D::drawQuad({ 3.f, -1.f }, { 0.5f, 2.f }, { 0.2f, 0.3f, 0.8f, 1.f });
    //Tempest::Renderer2D::drawRotatedQuad({ 0.f, 0.f - 0.1f }, { 10.f, 10.f }, glm::radians(45.f), _backgroundTexture, 20.f, { 0.4f, 0.2f, 0.3f, 1.f });

    Tempest::Renderer2D::endScene();
}

void Game2D::onEvent(Tempest::Event& e)
{
    _cameraController->onEvent(e);
}

void Game2D::onImGuiRender()
{
    TEMPEST_PROFILE_FUNCTION();
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

    ImGui::End();
}
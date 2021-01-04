#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "Level.h"

Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
{
    _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);
    _level = std::make_unique<Level>();
}

void Game2D::onAttach()
{
    TEMPEST_PROFILE_FUNCTION();

    _level->init();
    _cameraController->setZoomLevel(5.f);
}

void Game2D::onDetach()
{
    TEMPEST_PROFILE_FUNCTION();
}

void Game2D::onUpdate(Tempest::TimeStep timeStep)
{
    TEMPEST_PROFILE_FUNCTION();

    _cameraController->onUpdate(timeStep);

    Tempest::Renderer2D::resetStats();

    Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer2D::beginScene(_cameraController->getCamera());
    _level->onRender();
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

    auto stats = Tempest::Renderer2D::getStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.getTotalVertices());
    ImGui::Text("Indices: %d", stats.getTotalIndices());

    ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

    ImGui::End();
}
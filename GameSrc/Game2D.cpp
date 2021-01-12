#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Tempest/Audio/OpenALSoundBuffer.h"

#include "Level.h"

Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
{
    _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);
    _level = std::make_unique<Level>();

    _soundDevice = Tempest::SoundDevice::create();
    _soundBuffer = Tempest::SoundBuffer::create();
    _mySource = std::make_shared<Tempest::SoundSource>();
}

void Game2D::onAttach()
{
    TEMPEST_PROFILE_FUNCTION();

    _level->init();
    _cameraController->setZoomLevel(5.f);

    _spellSoundBuffer = _soundBuffer->addSoundEffect("Assets/Sounds/spell.wav");
    _magicFailSoundBuffer = _soundBuffer->addSoundEffect("Assets/Sounds/magicfail.wav");
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

    Tempest::EventDispatcher dispatcher(e);
    dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&Game2D::onKeyPressed, this, std::placeholders::_1));
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

bool Game2D::onKeyPressed(Tempest::PressedKeyEvent& e)
{
    if (e.getKeyCode() == TEMP_KEY_1)
    {
        _mySource->play(_spellSoundBuffer);
    }
    else if (e.getKeyCode() == TEMP_KEY_2)
    {
        _mySource->play(_magicFailSoundBuffer);
    }

    return false;
}

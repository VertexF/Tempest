#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include "Tempest/Events/Event.h"
#include "Tempest/Events/MouseEvents.h"

#include "Random.h"

Game2D::Game2D() : Layer("Game")
{
    auto& window = Tempest::Application::get().getWindow();

    _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);
    //_cameraController->setZoomLevel(0.2f);

    Random::init();
}

void Game2D::onAttach()
{
    TEMPEST_PROFILE_FUNCTION();

    _level.init();

    ImGuiIO io = ImGui::GetIO();
    _font = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans-Regular.ttf", 120.0f);
}

void Game2D::onDetach() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Game2D::onUpdate(Tempest::TimeStep timeStep) 
{
    TEMPEST_PROFILE_FUNCTION();

    _cameraController->onUpdate(timeStep);

    _time += timeStep;
    if (static_cast<int>(_time * 10.0f) % 8 > 4)
    {
        _blink = !_blink;
    }

    if (_level.isGameOver())
    {
        _gameState = GameState::GAME_OVER;
    }

    const auto& playerPos = _level.getPlayer().getPosition();
    _cameraController->setCameraPosition({ playerPos.x, playerPos.y, 0.0f });

    switch (_gameState)
    {
        case GameState::PLAY:
        {
            _level.onUpdate(timeStep);
            break;
        }
    }

    // Render
    Tempest::RendererCommands::setClearColour({ 0.f, 0.f, 0.f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer2D::beginScene(_cameraController->getCamera());

    _level.onRender();

    Tempest::Renderer2D::endScene();
}

void Game2D::onEvent(Tempest::Event& e)
{
    Tempest::EventDispatcher dispatcher(e);
    //dispatcher.dispatch<Tempest::MouseButtonEventPressed>(std::bind(&Game2D::onMouseButtonPressed, this, std::placeholders::_1));
    dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&Game2D::onButtonPressed, this, std::placeholders::_1));
    _cameraController->onEvent(e);
}

void Game2D::onImGuiRender() 
{
    TEMPEST_PROFILE_FUNCTION();

    switch (_gameState)
    {
    case GameState::PLAY:
    {
        uint32_t playerScore = _level.getPlayer().getScore();
        std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);

        ImGui::GetForegroundDrawList()->AddText(_font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());

        break;
    }
    case GameState::MAIN_MENU:
    {
        auto pos = ImGui::GetWindowPos();
        auto width = Tempest::Application::get().getWindow().getWidth();
        //auto height = Tempest::Application::get().getWindow().getHeight();

        pos.x += width * 0.5f - 570.0f;
        pos.y += 50.0f;

        //if (_blink)
        //{
            ImGui::GetForegroundDrawList()->AddText(_font, 120.0f, pos, 0xffffffff, "Click to Play!");
        //}

        break;
    }
    case GameState::GAME_OVER:
    {
        auto pos = ImGui::GetWindowPos();
        auto width = Tempest::Application::get().getWindow().getWidth();
        //auto height = Tempest::Application::get().getWindow().getHeight();

        pos.x += width * 0.5f - 590.0f;
        pos.y += 50.0f;

       // if (_blink)
        //{
            ImGui::GetForegroundDrawList()->AddText(_font, 120.0f, pos, 0xffffffff, "Press Space to Play Again!");
        //}

        pos.x += 440.0f;
        pos.y += 150.0f;

        uint32_t playerScore = _level.getPlayer().getScore();

        std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
        ImGui::GetForegroundDrawList()->AddText(_font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
        break;
    }
    case GameState::START:
    {
        auto pos = ImGui::GetWindowPos();
        auto width = Tempest::Application::get().getWindow().getWidth();

        pos.x += width * 0.5f - 470.0f;
        pos.y += 50.0f;

        // if (_blink)
         //{
        ImGui::GetForegroundDrawList()->AddText(_font, 120.0f, pos, 0xffffffff, "Press Space to Play!");
        //}

        pos.x += 160;
        pos.y += 150;

        ImGui::GetForegroundDrawList()->AddText(_font, 60.0f, pos, 0xffffffff, "Press Space to move!");

        pos.x += 150.0f;
        pos.y += 150.0f;

        uint32_t playerScore = _level.getPlayer().getScore();

        std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
        ImGui::GetForegroundDrawList()->AddText(_font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
        break;
    }

    }
}

bool Game2D::onButtonPressed(Tempest::PressedKeyEvent& e)
{
    if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE)) 
    {
        if (_gameState == GameState::GAME_OVER || _gameState == GameState::START)
        {
            _level.reset();
        }

        _gameState = GameState::PLAY;
        return false;
    }
}
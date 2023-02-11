#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Player.h"

#include "Global.h"

namespace 
{
    const int MAP_WIDTH = 64;
}

namespace game
{
    Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _scoreText = std::make_unique<Tempest::TextRenderer>(128.f);
        _levelText = std::make_unique<Tempest::TextRenderer>(128.f);
        _gameOverText = std::make_unique<Tempest::TextRenderer>(300.f);

        _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/stars.png");

        ENTITY_MANAGER.get(ENTITY_MANAGER.instantiate(EntityManager::EntityType::PLAYER))->init();
        ENTITY_MANAGER.get(ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER))->init();
        ENTITY_MANAGER.get(ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY))->init();
        _playerLives = ENTITY_MANAGER.getPlayer()->getLives();
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);
    }

    void Game2D::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Game2D::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _totalTime += timeStep;

        _cameraController->autoScroll(timeStep);
        _cameraController->onUpdate(timeStep);

        Tempest::Renderer2D::resetStats();

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        Tempest::Renderer2D::drawQuad({ 0.f, 0.f, 0.5f }, { 40.f, 20.f }, _backgroundTexture);

        char scoreText[13] = "Score : ";
        char intText[5];
        sprintf_s(intText, "%d", _score);
        strcat_s(scoreText, intText);

        _scoreText->displayText({ _cameraController->getCameraPosition().x + 4.f, _cameraController->getCameraPosition().y + 4.4f, 0.1f }, { 1.f, 1.f }, _squareColour, scoreText);

        char livesText[13] = "Lives : ";
        sprintf_s(intText, "%d", _playerLives);
        strcat_s(livesText, intText);

        _levelText->displayText({ _cameraController->getCameraPosition().x - 8.f, _cameraController->getCameraPosition().y + 4.4f, 0.1f }, { 1.f, 1.f }, _squareColour, livesText);
        if (ENTITY_MANAGER.isPlayerRemoved())
        {
            _isDead = true;
        }

        if (_score >= 2000)
        {
            _hasWon = true;
        }

        if (_isDead == false && _hasWon == false)
        {
            auto test = ENTITY_MANAGER.getEntities();
            for (auto iter = test.begin(); iter != test.end(); iter++) 
            {
                if (ENTITY_MANAGER.get(iter->first)) 
                {
                    ENTITY_MANAGER.get(iter->first)->onUpdate(timeStep);
                    if (ENTITY_MANAGER.get(iter->first)->isDead())
                    {
                        if (ENTITY_MANAGER.isPlayer(iter->first) == false) 
                        {
                            _score += 1000;
                        }
                        ENTITY_MANAGER.remove(iter->first);
                    }
                }
            }
        }
        else 
        {
            if (_hasWon && _isDead == false)
            {
                _gameOverText->displayText({ _cameraController->getCameraPosition().x - 6.f, _cameraController->getCameraPosition().y, -0.9f }, { 4.f, 4.f }, { 0.f, 1.f, 1.f, 1.f }, "You win!");
            }
            else
            {
                _gameOverText->displayText({ _cameraController->getCameraPosition().x - 6.f, _cameraController->getCameraPosition().y, -0.9f }, { 4.f, 4.f }, { 0.f, 1.f, 1.f, 1.f }, "You lose!");
            }
        }

        if (ENTITY_MANAGER.getPlayer())
        {
            _playerLives = ENTITY_MANAGER.getPlayer()->getLives();
        }
        else 
        {
            _playerLives = 0;
        }

        Tempest::Renderer2D::endScene();
    }

    void Game2D::onEvent(Tempest::Event& e)
    {
        _cameraController->onEvent(e);

        Tempest::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&Game2D::onKeyPressed, this, std::placeholders::_1));
        dispatcher.dispatch<Tempest::ReleasedKeyEvent>(std::bind(&Game2D::onKeyReleased, this, std::placeholders::_1));
    }

    void Game2D::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    bool Game2D::onKeyPressed(Tempest::PressedKeyEvent& /*e*/)
    {
        return false;
    }

    bool Game2D::onKeyReleased(Tempest::ReleasedKeyEvent& /*e*/)
    {
        return false;
    }

}

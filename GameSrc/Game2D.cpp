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

        _testText = std::make_unique<Tempest::TextRenderer>(128.f);

        _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/stars.png");

        ENTITY_MANAGER.instantiate(EntityManager::EntityType::PLAYER);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER);
        //Need this to stop thing exploding.
        //ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ENEMY);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER);
        ENTITY_MANAGER.instantiate(EntityManager::EntityType::ATTACKER);

        for (uint32_t i = 0; i < static_cast<uint32_t>(ENTITY_MANAGER.size()); i++)
        {
            ENTITY_MANAGER.get(i)->init();
        }

        ENTITY_MANAGER.get(3)->setPosition( { 12.f, -4.f, -0.6f } );
        ENTITY_MANAGER.get(4)->setPosition({ 12.f, 8.f, -0.6f });
        ENTITY_MANAGER.get(5)->setPosition({ 9.f, -5.f, -0.6f });
        ENTITY_MANAGER.get(6)->setPosition({ 12.f, 4.f, -0.6f });
        ENTITY_MANAGER.get(7)->setPosition({ 15.f, -4.f, -0.6f });

        ENTITY_MANAGER.get(3)->setPosition({ 15.f, 0.f, -0.6f });
        ENTITY_MANAGER.get(4)->setPosition({ 15.f, 5.f, -0.6f });
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

        _cameraController->onUpdate(timeStep);

        Tempest::Renderer2D::resetStats();

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        Tempest::Renderer2D::drawQuad({ _cameraController->getCameraPosition().x, _cameraController->getCameraPosition().y, 0.5f }, { 20.f, 10.f }, _backgroundTexture);

        _testText->displayText({ _cameraController->getCameraPosition().x - 6.f, _cameraController->getCameraPosition().y + 4.f, 0.1f}, { 1.f, 1.f }, _squareColour, std::string("Score : " + std::to_string(_score)).c_str());
        if (ENTITY_MANAGER.isPlayerRemoved() == false)
        {
            ENTITY_MANAGER.getPlayer()->setVelocity(_cameraController->getCameraPosition());
        }
        else 
        {
            _isDead = true;
        }

        if (_score >= 2000)
        {
            _hasWon = true;
        }

        if (_isDead == false && _hasWon == false)
        {
            for (uint32_t i = 0; i < ENTITY_MANAGER.size(); i++)
            {
                if (ENTITY_MANAGER.get(i) != nullptr)
                {
                    ENTITY_MANAGER.get(i)->onUpdate(timeStep);
                    if (ENTITY_MANAGER.get(i)->isDead())
                    {
                        if (ENTITY_MANAGER.isPlayer(i) == false)
                        {
                            _score += 1000;
                        }
                        ENTITY_MANAGER.remove(i);
                        break;
                    }
                }
            }
        }
        else 
        {
            if (_hasWon && _isDead == false)
            {
                _testText->displayText({ _cameraController->getCameraPosition().x - 6.f, _cameraController->getCameraPosition().y, -0.9f }, { 4.f, 4.f }, { 0.f, 1.f, 1.f, 1.f }, "You win!");
            }
            else
            {
                _testText->displayText({ _cameraController->getCameraPosition().x - 6.f, _cameraController->getCameraPosition().y, -0.9f }, { 4.f, 4.f }, { 0.f, 1.f, 1.f, 1.f }, "You lose!");
            }
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

    bool Game2D::onKeyPressed(Tempest::PressedKeyEvent& e)
    {
        return false;
    }

    bool Game2D::onKeyReleased(Tempest::ReleasedKeyEvent& e) 
    {
        return false;
    }

}

#include "PreComp.h"
#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Tempest/Core/Input.h"
#include "Tempest/Core/KeyCodes.h"
#include "Tempest/Core/TimeStep.h"

#include "Global.h"

namespace game
{
    Player::Player(int id) : BaseEntity(id), _currentState(CURRENT_STATE::FLYING)
    {
        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/ships.png");
        _astroid = Tempest::Texture2D::create("Assets/Textures/astroid.png");

        _shipTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 0, 3 }, { 256, 256 });

        //Smoke
        _smokeParticalProps.position = { 0.f, 0.f };

        _smokeParticalProps.velocity = { -2.f, 0.f };
        _smokeParticalProps.velocityVariation = { 4.f, 2.f };

        _smokeParticalProps.beginSize = 0.2f;
        _smokeParticalProps.endSize = 0.0f;
        _smokeParticalProps.sizeVarition = 0.15f;

        _smokeParticalProps.colourBegin = { 0.8f, 0.8f, 0.8f, 1.f };
        _smokeParticalProps.colourEnd = { 0.6f, 0.6f, 0.6f, 1.f };

        _smokeParticalProps.lifeTime = 4.f;

        //fire
        _fireParticalProps.position = { 0.f, 0.f };

        _fireParticalProps.velocity = { -2.f, 0.f };
        _fireParticalProps.velocityVariation = { 3.f, 1.f };

        _fireParticalProps.beginSize = 0.2f;
        _fireParticalProps.endSize = 0.0f;
        _fireParticalProps.sizeVarition = 0.3f;

        _fireParticalProps.colourBegin = { 254.f / 255.f, 109.f / 255.f, 41.f / 255.f, 1.f };
        _fireParticalProps.colourEnd = { 254.f / 255.f, 212.f / 255.f, 123.f / 255.f , 1.f };

        _fireParticalProps.lifeTime = 1.f;
    }

    void Player::init()
    {
        reset();
        _bullet = std::make_unique<game::Bullet>(entityID, true);

        testRect.position = { 5.f, 0.f, 0.f };
    }

    void Player::loadAssets()
    {
        TEMPEST_PROFILE_FUNCTION();

    }

    void Player::onUpdate(Tempest::TimeStep ts)
    {
        TEMPEST_PROFILE_FUNCTION();

        collisionRect.position = collisionRect.velocity;
        _time += ts;

        switch (_currentState)
        {
        case CURRENT_STATE::FLYING:
            for(const auto & ship : ENTITY_MANAGER.getEnemies())
            {
                if (Tempest::AABBCollision::PointVsRect(ship->getBulletPosition(), collisionRect))
                {
                    _lives -= 1;
                    _currentState = CURRENT_STATE::DAMAGED;
                }

                //const Rect& movingRect, const TimeStep timeStep, const Rect staticRect, glm::vec2& outContactPoint, glm::vec2& outContantNormal, float &contactTime
                if (Tempest::AABBCollision::RectVsRect(collisionRect, ship->getCollisionRect()))
                {
                    _lives -= 1;
                    _currentState = CURRENT_STATE::DAMAGED;
                }
            }
            colour = { 1.f, 1.f, 1.f, 1.f };
            break;
        case CURRENT_STATE::DAMAGED:
            colour = { 1.f, 0.0f, 0.0f, 1.f };

            _totalTime += ts;
            if (_totalTime > _invisibilityTime)
            {
                _totalTime = 0.f;
                _currentState = _currentState = CURRENT_STATE::FLYING;
            }

            break;
        }

        glm::vec2 emissionPoint = { collisionRect.position.x, collisionRect.position.y };
        glm::vec2 particalsPosition = glm::vec2(collisionRect.position.x - 0.4f, collisionRect.position.y);
        glm::vec2 particalsVelocity = glm::vec2(collisionRect.velocity.x, collisionRect.velocity.y);
        float rotation = glm::radians(getRotation());
        _fireParticalProps.position = particalsPosition;
        _fireParticalProps.velocity.y = -particalsVelocity.y * 0.2f - 0.2f;
        _particalSystem.emit(_fireParticalProps);

        if (_time > _smokeEmitTime)
        {
            _smokeParticalProps.position = collisionRect.position;
            _smokeParticalProps.position.x -= 0.5f;
            _particalSystem.emit(_smokeParticalProps);
            _smokeEmitTime += _smokeInterval;
        }

        _particalSystem.onUpdate(ts);

        _bullet->onUpdate(ts);

        onRender();
    }

    void Player::onRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        Tempest::Renderer2D::drawQuad({ collisionRect.position.x, collisionRect.position.y, -0.5f }, collisionRect.size, _shipTexture, 1.f, colour);

        Tempest::Renderer2D::drawQuad({ testRect.position.x, testRect.position.y, -0.5f }, testRect.size, _astroid);

        _particalSystem.onRender();

    }

    void Player::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Player::reset()
    {
        colour = { 1.f, 0.f, 0.f, 1.f };
        collisionRect.position = { 0.f, 0.f, 0.f };
        collisionRect.velocity = { 0.f, 0.f, 0.f };
    }

    const glm::vec3 Player::getBulletPosition() const
    {
        return _bullet->getPosition();
    }

    int Player::getID() const
    {
        return entityID;
    }

    bool Player::isDead() const
    {
        return (_lives <= 0);
    }
}
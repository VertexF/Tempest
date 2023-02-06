#include "PreComp.h"
#include "Enemy.h"

#include <Tempest.h>

namespace game
{
    Enemy::Enemy(int id) : BaseEntity(id), _lives(3)
    {
        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/ships.png");
        _shipTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 0, 1 }, { 256, 256 });

        //Smoke
        _smokeParticalProps.position = { 0.f, 0.f };

        _smokeParticalProps.velocity = { 2.f, 0.f };
        _smokeParticalProps.velocityVariation = { 4.f, 2.f };

        _smokeParticalProps.beginSize = 0.2f;
        _smokeParticalProps.endSize = 0.0f;
        _smokeParticalProps.sizeVarition = 0.15f;

        _smokeParticalProps.colourBegin = { 0.8f, 0.8f, 0.8f, 1.f };
        _smokeParticalProps.colourEnd = { 0.6f, 0.6f, 0.6f, 1.f };

        _smokeParticalProps.lifeTime = 4.f;

        //fire
        _fireParticalProps.position = { 0.f, 0.f };

        _fireParticalProps.velocity = { 2.f, 0.f };
        _fireParticalProps.velocityVariation = { 3.f, 1.f };

        _fireParticalProps.beginSize = 0.2f;
        _fireParticalProps.endSize = 0.0f;
        _fireParticalProps.sizeVarition = 0.3f;

        _fireParticalProps.colourBegin = { 254.f / 255.f, 109.f / 255.f, 41.f / 255.f, 1.f };
        _fireParticalProps.colourEnd = { 254.f / 255.f, 212.f / 255.f, 123.f / 255.f , 1.f };

        _fireParticalProps.lifeTime = 1.f;
    }

    void Enemy::init()
    {
        spawn();
        _currentState = CURRENT_STATE::FLYING;
        _bullet = std::make_unique<Bullet>(entityID, false);
        _bullet->setColour({ 1.0f, 0.5f, 0.0f, 1.f });
    }

    void Enemy::onRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        Tempest::Renderer2D::drawQuad({ collisionRect.position.x, collisionRect.position.y, -0.5f }, collisionRect.size, _shipTexture, 1.f, colour);

        _particalSystem.onRender();
    }

    void Enemy::onUpdate(Tempest::TimeStep timeStep)
    {
        switch (_currentState)
        {
        case CURRENT_STATE::FLYING:
            if (ENTITY_MANAGER.isPlayerRemoved() == false)
            {
                if (Tempest::AABBCollision::PointVsRect(ENTITY_MANAGER.getPlayer()->getBulletPosition(), collisionRect))
                {
                    _lives -= 1;
                    _currentState = CURRENT_STATE::DAMAGED;
                }
            }
            colour = { 1.f, 1.f, 1.f, 1.f };
            break;
        case CURRENT_STATE::DAMAGED:
            colour = { 1.f, 0.f, 0.f, 1.f };

            _totalTime += timeStep;
            if (_totalTime > _invisibilityTime)
            {
                _totalTime = 0.f;
                _currentState = _currentState = CURRENT_STATE::FLYING;
            }

            break;
        }

        move(timeStep);
        fire(timeStep);

        glm::vec2 emissionPoint = { collisionRect.position.x, collisionRect.position.y };
        glm::vec2 particalsPosition = glm::vec2(collisionRect.position.x + 0.5f, collisionRect.position.y);
        glm::vec2 particalsVelocity = glm::vec2(collisionRect.velocity.x, collisionRect.velocity.y);
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

        _particalSystem.onUpdate(timeStep);

        onRender();
    }

    void Enemy::spawn()
    {
        collisionRect.acceleration = { 0.f, 0.f, 0.f };
        collisionRect.velocity = { 0.f, 0.f, 0.f };
        collisionRect.position = { 3.f, 0.f, 0.f };
    }

    void Enemy::move(Tempest::TimeStep timeStep) 
    {
        _movementTime += timeStep;
        collisionRect.position.y += ((5.f * glm::cos(_movementTime)) * timeStep);

        if (_movementTime >= std::numeric_limits<float>::max())
        {
            _movementTime = 0.f;
        }
    }

    void Enemy::fire(Tempest::TimeStep timeStep)
    {
        _bullet->onUpdate(timeStep);
    }

    const glm::vec3 Enemy::getBulletPosition() const 
    {
        return _bullet->getPosition();
    }

    int Enemy::getID() const
    {
        return entityID;
    }

    bool Enemy::isDead() const
    {
        return (_lives <= 0);
    }
}
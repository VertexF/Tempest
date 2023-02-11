#include "PreComp.h"
#include "Attacker.h"

#include <Tempest.h>

namespace game
{
    Attacker::Attacker(int id) : BaseEntity(id), _bulletEmitter(false), _lives(3)
    {
        TEMPEST_PROFILE_FUNCTION();
        _shipTexture = Tempest::SubTexture2D::createFromCoords(RESOURCE_MANAGER.getSpriteSheet(ResourceManager::SPRITESHEET_TYPE::SHIP), {0, 2}, {256, 256});
        _laserSoundBuffer = AUDIO_MANAGER.addSoundEffect("Assets/Audio/laser.wav");
        _mySource = std::make_unique<Tempest::SoundSource>();

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

        _bulletParticalProps.position = { 3.f, 0.f };

        _bulletParticalProps.velocity = { -15.f, 0.f };
        _bulletParticalProps.velocityVariation = { 0.f, 0.f };

        _bulletParticalProps.beginSize = 1.0f;
        _bulletParticalProps.endSize = 0.0f;
        _bulletParticalProps.sizeVarition = 0.0f;

        _bulletParticalProps.colourBegin = { 254.f / 255.f, 109.f / 255.f, 41.f / 255.f, 1.f };
        _bulletParticalProps.colourEnd = { 254.f / 255.f, 212.f / 255.f, 123.f / 255.f , 1.f };

        _bulletParticalProps.lifeTime = 0.5f;
    }

    void Attacker::init()
    {
        spawn();
        _currentState = CURRENT_STATE::FLYING;
    }

    void Attacker::onRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        Tempest::Renderer2D::drawQuad({ collisionRect.position.x, collisionRect.position.y, -0.5f }, collisionRect.size, _shipTexture, 1.f, colour);

        _particalSystem.onRender();
        _bulletEmitter.onRender();
    }

    void Attacker::onUpdate(Tempest::TimeStep timeStep)
    {
        _time += timeStep;

        switch (_currentState)
        {
        case CURRENT_STATE::FLYING:
            if (ENTITY_MANAGER.isPlayerRemoved() == false)
            {
                for (const auto& bullet : ENTITY_MANAGER.getPlayer()->getBullets())
                {
                    if (Tempest::AABBCollision::PointVsRect(bullet.position, collisionRect))
                    {
                        _lives -= 1;
                        _currentState = CURRENT_STATE::DAMAGED;
                    }
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
            _bulletParticalProps.position = glm::vec2(collisionRect.position.x - 0.4f, collisionRect.position.y);
            _bulletEmitter.emit(_bulletParticalProps);
            _mySource->play(_laserSoundBuffer);
        }

        _particalSystem.onUpdate(timeStep);
        _bulletEmitter.onUpdate(timeStep);

        onRender();
    }

    void Attacker::spawn()
    {
        collisionRect.acceleration = { 0.f, 0.f, 0.f };
        collisionRect.velocity = { 0.f, 0.f, 0.f };
        collisionRect.position = { 12.f, 0.f, 4.f };
    }

    void Attacker::move(Tempest::TimeStep timeStep)
    {
        _movementTime += timeStep;
        collisionRect.position.y += (2.f * glm::cos(_movementTime)) * timeStep;
        collisionRect.position.x -= 2.f * timeStep;

        if (_movementTime >= std::numeric_limits<float>::max())
        {
            _movementTime = 0.f;
        }
    }

    void Attacker::fire(Tempest::TimeStep /*timeStep*/)
    {
    }

    const glm::vec3 Attacker::getBulletPosition() const
    {
        return glm::vec3(0.f);
    }

    int Attacker::getID() const
    {
        return entityID;
    }

    std::vector<BulletPartical::Partical> Attacker::getBullets() const
    {
        return _bulletEmitter.getParticalPool();
    }

    bool Attacker::isDead() const
    {
        return (_lives <= 0);
    }
}
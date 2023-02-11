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
    Player::Player(int id) : BaseEntity(id), _bulletEmitter(true), _currentState(CURRENT_STATE::FLYING)
    {
        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/ships.png");
        _astroid = Tempest::Texture2D::create("Assets/Textures/astroid.png");
        _laserSoundBuffer = AUDIO_MANAGER.addSoundEffect("Assets/Audio/EnemyLaser.wav");
        _mySource = std::make_unique<Tempest::SoundSource>();

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

        //Bullet
        _bulletParticalProps.position = { 0.f, 0.f };

        _bulletParticalProps.velocity = { 15.f, 0.f };
        _bulletParticalProps.velocityVariation = { 0.f, 0.f };

        _bulletParticalProps.beginSize = 1.0f;
        _bulletParticalProps.endSize = 0.0f;
        _bulletParticalProps.sizeVarition = 0.0f;

        _bulletParticalProps.colourBegin = { 254.f / 255.f, 109.f / 255.f, 41.f / 255.f, 1.f };
        _bulletParticalProps.colourEnd = { 254.f / 255.f, 212.f / 255.f, 123.f / 255.f , 1.f };

        _bulletParticalProps.lifeTime = 0.5f;
    }

    void Player::init()
    {
        reset();
        testRect.position = { 5.f, 0.f, 0.f };
    }

    void Player::loadAssets()
    {
        TEMPEST_PROFILE_FUNCTION();

    }

    void Player::onUpdate(Tempest::TimeStep ts)
    {
        TEMPEST_PROFILE_FUNCTION();

        _time += ts;

        if (Tempest::Input::isKeyPressed(TEMP_KEY_W))
        {
            collisionRect.velocity.y += 4.f * ts;
        }
        if (Tempest::Input::isKeyPressed(TEMP_KEY_S))
        {
            collisionRect.velocity.y -= 4.f * ts;
        }

        if (Tempest::Input::isKeyPressed(TEMP_KEY_A))
        {
            collisionRect.velocity.x -= 4.f * ts;
        }
        if (Tempest::Input::isKeyPressed(TEMP_KEY_D))
        {
            collisionRect.velocity.x += 4.f * ts;
        }

        if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE))
        {
            if (_time > _smokeEmitTime)
            {
                _bulletParticalProps.position = glm::vec2(collisionRect.position.x + 0.4f, collisionRect.position.y);
                _bulletEmitter.emit(_bulletParticalProps);
                _mySource->play(_laserSoundBuffer);
            }
        }

        collisionRect.position = collisionRect.velocity;

        switch (_currentState)
        {
        case CURRENT_STATE::FLYING:
            for(const auto & ship : ENTITY_MANAGER.getEnemies())
            {
                for (const auto& bullet : ship->getBullets())
                {
                    if (Tempest::AABBCollision::PointVsRect(bullet.position, collisionRect))
                    {
                        _lives -= 1;
                        _currentState = CURRENT_STATE::DAMAGED;
                        break;
                    }
                }

                if (Tempest::AABBCollision::RectVsRect(collisionRect, ship->getCollisionRect()))
                {
                    _lives -= 1;
                    _currentState = CURRENT_STATE::DAMAGED;
                    break;
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
        _fireParticalProps.position = particalsPosition;
        _fireParticalProps.velocity.y = -particalsVelocity.y * 0.2f - 0.2f;
        _particalSystem.emit(_fireParticalProps);

        if (_time > _smokeEmitTime)
        {
            _smokeParticalProps.position = collisionRect.position;
            _smokeParticalProps.position.x -= 0.5f;
            _particalSystem.emit(_smokeParticalProps);
            _smokeEmitTime += _smokeInterval;

            //_bulletParticalProps.position = glm::vec2(collisionRect.position.x + 0.4f, collisionRect.position.y);
            //_bulletEmitter.emit(_bulletParticalProps);
        }

        _particalSystem.onUpdate(ts);
        _bulletEmitter.onUpdate(ts);

        onRender();
    }

    void Player::onRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        Tempest::Renderer2D::drawQuad({ collisionRect.position.x, collisionRect.position.y, -0.5f }, collisionRect.size, _shipTexture, 1.f, colour);

        Tempest::Renderer2D::drawQuad({ testRect.position.x, testRect.position.y, -0.5f }, testRect.size, _astroid);

        _particalSystem.onRender();
        _bulletEmitter.onRender();

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
        //_bulletEmitter.getParticalPool();
        return glm::vec3(_bulletParticalProps.position.x, _bulletParticalProps.position.y, -0.4);
    }

    std::vector<BulletPartical::Partical> Player::getBullets() const
    {
        return _bulletEmitter.getParticalPool();
    }

    int Player::getID() const
    {
        return entityID;
    }

    bool Player::isDead() const
    {
        return (_lives <= 0);
    }

    uint32_t Player::getLives() const
    {
        return _lives;
    }
}
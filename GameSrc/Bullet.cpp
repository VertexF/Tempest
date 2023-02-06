#include "PreComp.h"
#include "Bullet.h"

#include <Tempest.h>

#include "Global.h"

namespace game 
{
    Bullet::Bullet(int id, bool isPlayer) : BaseEntity(id), _currentState(BULLET_STATE::READY)
    {
        collisionRect.position = ENTITY_MANAGER.get(entityID)->getPosition();

        _soundDevice = Tempest::SoundDevice::create();
        _soundBuffer = Tempest::SoundBuffer::create();
        _mySource = std::make_shared<Tempest::SoundSource>();

        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/ships.png");
        _laserSoundBuffer = _soundBuffer->addSoundEffect("Assets/Audio/laser.wav");

        if(isPlayer)
            _bulletTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 2 }, { 256, 256 });
        else
            _bulletTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 3 }, { 256, 256 });
    }

    void Bullet::onRender()
    {
        Tempest::Renderer2D::drawQuad({ collisionRect.position.x, collisionRect.position.y, -0.4f }, { 1.0f, 1.0f }, _bulletTexture);
    }

    void Bullet::onUpdate(Tempest::TimeStep ts)
    {
        if (ENTITY_MANAGER.isPlayer(entityID))
        {
            switch (_currentState)
            {
            case BULLET_STATE::READY:
            if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE))
            {
                collisionRect.position.x += 10.f * ts;
                _currentState = BULLET_STATE::FIRE;
                _mySource->play(_laserSoundBuffer);
            }
            if (ENTITY_MANAGER.get(entityID) != nullptr)
                collisionRect.position = ENTITY_MANAGER.get(entityID)->getPosition();

            break;
        case BULLET_STATE::FIRE:
            collisionRect.position.x += 10.f * ts;

            _totalTime += ts;
            if (_totalTime > lifeTime)
            {
                _totalTime = 0.f;
                _currentState = BULLET_STATE::RESET;
            }
            break;
        case BULLET_STATE::RESET:
            if (ENTITY_MANAGER.get(entityID) != nullptr)
                collisionRect.position = ENTITY_MANAGER.get(entityID)->getPosition();
            _currentState = BULLET_STATE::READY;
            break;
            }
        }
        else 
        {
            switch (_currentState)
            {
            case BULLET_STATE::READY:
                //position.x -= 10.f * ts;
                _currentState = BULLET_STATE::FIRE;
                _mySource->play(_laserSoundBuffer);
                if (ENTITY_MANAGER.get(entityID) != nullptr)
                    collisionRect.position = ENTITY_MANAGER.get(entityID)->getPosition();

                break;
            case BULLET_STATE::FIRE:
                collisionRect.position.x -= 10.f * ts;

                _totalTime += ts;
                if (_totalTime > lifeTime)
                {
                    _totalTime = 0.f;
                    _currentState = BULLET_STATE::RESET;
                }
                break;
            case BULLET_STATE::RESET:
                if(ENTITY_MANAGER.get(entityID) != nullptr)
                    collisionRect.position = ENTITY_MANAGER.get(entityID)->getPosition();
                _currentState = BULLET_STATE::READY;
                break;
            }
        }

        onRender();
    }

    void Bullet::setColour(const glm::vec4& colour)
    {
        this->colour = colour;
    }

    const glm::vec3 Bullet::getBulletPosition() const
    {
        return collisionRect.position;
    }

    int Bullet::getID() const
    {
        return entityID;
    }
}
#include "PreComp.h"
#include "BulletParticles.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Tempest/Core/Random.h"
#include "Tempest/Renderer/Renderer2D.h"

namespace game
{
    BulletPartical::BulletPartical(bool isPlayer)
    {
        TEMPEST_PROFILE_FUNCTION();
        _particalPool.resize(11);

        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/ships.png");

        if (isPlayer)
            _bulletTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 2 }, { 256, 256 });
        else
            _bulletTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 3 }, { 256, 256 });
    }

    void BulletPartical::emit(const ParticalProps& particalProps)
    {
        TEMPEST_PROFILE_FUNCTION();
        Partical& partical = _particalPool[_poolIndex];
        partical.active = true;
        partical.position = particalProps.position;
        partical.rotation = Random::getFloat() * 2.f * glm::pi<float>();

        partical.velocity = particalProps.velocity;
        partical.velocity.x += particalProps.velocityVariation.x * (Random::getFloat() - 0.5f);
        partical.velocity.y += particalProps.velocityVariation.y * (Random::getFloat() - 0.5f);

        partical.colourBegin = particalProps.colourBegin;
        partical.colourEnd = particalProps.colourEnd;

        partical.beginSize = particalProps.beginSize + particalProps.sizeVarition * (Random::getFloat() - 0.5f);
        partical.endSize = particalProps.endSize;

        partical.lifeTime = particalProps.lifeTime;
        partical.lifeRemaining = particalProps.lifeTime;

        _poolIndex = --_poolIndex % _particalPool.size();
    }

    void BulletPartical::onUpdate(Tempest::TimeStep ts)
    {
        TEMPEST_PROFILE_FUNCTION();
        for (auto& partical : _particalPool)
        {
            if (partical.active == false)
            {
                continue;
            }

            if (partical.lifeRemaining <= 0.f)
            {
                partical.active = false;
                continue;
            }

            partical.lifeRemaining -= ts;
            partical.position += partical.velocity * static_cast<float>(ts);
            partical.rotation += 0.01f * ts;
        }
    }

    void BulletPartical::onRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        for (auto& partical : _particalPool)
        {
            if (partical.active == false)
            {
                continue;
            }

            float life = partical.lifeRemaining / partical.lifeTime;
            glm::vec4 colour = glm::lerp(partical.colourEnd, partical.colourBegin, life);

            float size = glm::lerp(partical.endSize, partical.beginSize, life);
            Tempest::Renderer2D::drawQuad({ partical.position.x, partical.position.y, -0.4f }, { 1.f, 1.f }, _bulletTexture, 1.f, colour);
        }
    }

    std::vector<BulletPartical::Partical> BulletPartical::getParticalPool() const
    {
        return _particalPool;
    }
}
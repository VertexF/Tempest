#include "PreComp.h"
#include "ParticalSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Tempest/Core/Random.h"
#include "Tempest/Renderer/Renderer2D.h"

namespace Tempest
{
    ParticalSystem::ParticalSystem()
    {
        TEMPEST_PROFILE_FUNCTION();
        _particalPool.resize(1000);
    }

    void ParticalSystem::emit(const ParticalProps& particalProps)
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

    void ParticalSystem::onUpdate(TimeStep ts)
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

    void ParticalSystem::onRender()
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
            colour.a = colour.a * life;

            float size = glm::lerp(partical.endSize, partical.beginSize, life);
            Renderer2D::drawRotatedQuad({ partical.position.x, partical.position.y, -0.8f }, { size, size }, partical.rotation, colour);
        }
    }

    std::vector<ParticalSystem::Partical> ParticalSystem::getParticalPool() const
    {
        return _particalPool;
    }
}
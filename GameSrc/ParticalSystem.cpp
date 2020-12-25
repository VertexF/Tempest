#include "PreComp.h"
#include "ParticalSystem.h"

#include "Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticalSystem::ParticalSystem() 
{
    _particalPool.resize(1000);
}

void ParticalSystem::emit(const ParticalProps& particalProps) 
{
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

void ParticalSystem::onUpdate(Tempest::TimeStep ts) 
{
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
        Tempest::Renderer2D::drawRotatedQuad(partical.position, {size, size}, partical.rotation, colour);
    }
}
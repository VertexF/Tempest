#ifndef BULLET_PARTICLES_HDR
#define BULLET_PARTICLES_HDR

#include <glm/glm.hpp>

#include "Tempest/Core/TimeStep.h"
#include "Tempest/Renderer/SubTexture2D.h"
#include "Tempest/Renderer/Texture.h"

namespace game
{
    struct ParticalProps
    {
        glm::vec2 position;
        glm::vec2 velocity, velocityVariation;
        glm::vec4 colourBegin, colourEnd;
        float beginSize, endSize, sizeVarition;
        float lifeTime = 1.f;
    };

    class BulletPartical
    {
    public:
        struct Partical
        {
            glm::vec2 position = { -99.f, -99.f };
            glm::vec2 velocity, velocityVariation;
            glm::vec4 colourBegin, colourEnd;

            float rotation = 0.f;
            float beginSize, endSize;

            float lifeTime = 1.f;
            float lifeRemaining = 0.f;

            bool active = false;
        };

    public:
        BulletPartical(bool isPlayer);

        void emit(const ParticalProps& particalProps);

        void onUpdate(Tempest::TimeStep ts);
        void onRender();

        std::vector<Partical> getParticalPool() const;
    private:
        std::vector<Partical> _particalPool;

        Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;
        Tempest::ref<Tempest::SubTexture2D> _bulletTexture;

        uint32_t _poolIndex = 10;
    };
}

#endif //!BULLET_PARTICLES_HDR
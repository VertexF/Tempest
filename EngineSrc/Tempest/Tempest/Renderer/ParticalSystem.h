#ifndef PARTICAL_SYSTEM_HDR
#define PARTICAL_SYSTEM_HDR

#include <glm/glm.hpp>

#include "Tempest/Core/TimeStep.h"

namespace Tempest
{
    struct ParticalProps
    {
        glm::vec2 position;
        glm::vec2 velocity, velocityVariation;
        glm::vec4 colourBegin, colourEnd;
        float beginSize, endSize, sizeVarition;
        float lifeTime = 1.f;
    };

    class ParticalSystem
    {
    public:
        ParticalSystem();

        void emit(const ParticalProps& particalProps);

        void onUpdate(TimeStep ts);
        void onRender();
    private:
        struct Partical
        {
            glm::vec2 position;
            glm::vec2 velocity, velocityVariation;
            glm::vec4 colourBegin, colourEnd;

            float rotation = 0.f;
            float beginSize, endSize;

            float lifeTime = 1.f;
            float lifeRemaining = 0.f;

            bool active = false;
        };

        std::vector<Partical> _particalPool;
        uint32_t _poolIndex = 999;
    };
}
#endif // !PARTICAL_SYSTEM_HDR

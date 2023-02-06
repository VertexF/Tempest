#ifndef RECT_HDR
#define RECT_HDR

#include <glm/glm.hpp>

namespace Tempest 
{
    struct Rect
    {
        glm::vec3 position = { 0.f, 0.f, 0.f };
        glm::vec3 velocity = { 0.f, 0.f, 0.f };
        glm::vec3 acceleration = { 0.f, 0.f, 0.f };

        glm::vec2 size = { 1.f, 1.f };
        glm::vec2 halfSpace = { size.x / 2, size.y / 2 };
    };
}

#endif // !RECT_HDR

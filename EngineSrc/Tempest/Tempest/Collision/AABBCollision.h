#ifndef AABB_COLLISION_HDR
#define AABB_COLLISION_HDR

#include <glm/glm.hpp>
#include <functional>
#include <algorithm>

#include "Tempest/Core/TimeStep.h"

namespace Tempest 
{
    struct AABBCollision 
    {
        static bool PointVsRect(const glm::vec2 &point, const Rect& rect) 
        {
            return (point.x >= rect.position.x - rect.halfSpace.x && point.y >= rect.position.y - rect.halfSpace.y && point.x < rect.position.x + rect.halfSpace.x && point.y < rect.position.y + rect.halfSpace.y);
        }

        //Note: this is just a static none moving AABB
        static bool RectVsRect(const Rect& rect1, const Rect& rect2) 
        {
            return (rect1.position.x < rect2.position.x + rect2.size.x && rect1.position.x + rect1.size.x > rect2.position.x &&
                    rect1.position.y < rect2.position.y + rect2.size.y && rect1.position.y + rect1.size.y > rect2.position.y);
        }

        static bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDirection, const Rect& target, glm::vec2 &outContactPoint, glm::vec2 &outContactNormal, float& outTimeNear)
        {
            outContactPoint = { 0.f, 0.f };
            outContactNormal = { 0.f, 0.f };

            glm::vec2 multableRayOrigin = rayOrigin;

            //Note to self, apprently this helps caching do this more often.
            glm::vec2 inverseDirection = 1.f / rayDirection;
            glm::vec2 targetPosition(target.position.x, target.position.y);

            glm::vec2 tNear = (targetPosition - rayOrigin) * inverseDirection;
            glm::vec2 tFar = (targetPosition + target.size - rayOrigin) * inverseDirection;

            if (std::isnan(tFar.y) || std::isnan(tFar.x)) 
            {
                return false;
            }
            if (std::isnan(tNear.y) || std::isnan(tNear.x))
            {
                return false;
            }

            //Sort distances
            if (tNear.x > tFar.x) 
            {
                std::swap(tNear.x, tFar.x);
            }
            if (tNear.y > tFar.y)
            {
                std::swap(tNear.y, tFar.y);
            }

            if (tNear.x > tFar.y || tNear.y > tFar.y) 
            {
                return false;
            }

            outTimeNear = std::max(tNear.x, tNear.y);
            float tHitFar = std::min(tFar.x, tFar.y);

            if (tHitFar < 0.f)
            {
                return false;
            }

            //Contact point.
            outContactPoint = rayOrigin + outTimeNear * inverseDirection;

            if (tNear.x > tNear.y) 
            {
                if (inverseDirection.x < 0) 
                {
                    outContactNormal = { 1, 0 };
                }
                else 
                {
                    outContactNormal = { -1, 0 };
                }
            }
            else if (tNear.x < tNear.y) 
            {
                if (inverseDirection.y < 0)
                {
                    outContactNormal = { 0, 1 };
                }
                else
                {
                    outContactNormal = { 0, -1 };
                }
            }

            return true;
        }

        static bool DynamicRectVsRect(const Rect& movingRect, const TimeStep /*timeStep*/, const Rect staticRect, glm::vec2& outContactPoint, glm::vec2& outContantNormal, float& contactTime)
        {
            //Fix this later
            //if (movingRect.velocity == glm)
            //{
            //    return false;
            //}

            Rect expendedTarget;
            expendedTarget.position = staticRect.position - glm::vec3(movingRect.halfSpace.x, movingRect.halfSpace.y, 0.f);
            expendedTarget.size = staticRect.size + movingRect.size;
            //glm::vec2 movingRect2DVel;
            //movingRect2DVel.x = movingRect.velocity.x;
            //movingRect2DVel.y = movingRect.velocity.y;
            //movingRect2DVel *= timeStep;

            glm::vec2 finalPosition = glm::vec2(staticRect.position.x, staticRect.position.y);
            finalPosition += movingRect.halfSpace;

            if (RayVsRect(finalPosition, movingRect.velocity, expendedTarget, outContactPoint, outContantNormal, contactTime))
            {
                return (contactTime >= 0.f && contactTime < 1.f);
            }
            else 
            {
                return false;
            }
        }
    };
}

#endif // !AABB_COLLISION_HDR

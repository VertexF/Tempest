#ifndef BASE_ENTITY_HDR
#define BASE_ENTITY_HDR

#include <memory>
#include <string>

#include <Tempest.h>

#include "BulletParticles.h"

namespace game
{
    class BaseEntity
    {
    public:
        BaseEntity(int id);
        virtual ~BaseEntity() = default;

        double getAge() const;

        double getBottom() const { return collisionRect.position.y; }
        double getLeft() const { return collisionRect.position.x; }
        double getRight() const { return collisionRect.position.x + collisionRect.size.x; }
        double getTop() const { return collisionRect.position.y + collisionRect.size.y; }
        double getCenterX() const { return getRight() / 2.0; }
        double getCenterY() const { return getTop() / 2.0; }
        virtual void onUpdate(Tempest::TimeStep timeStep) = 0;

        virtual void init() {}

        virtual glm::vec3 getAcceleration() const;
        virtual void setAcceleration(const glm::vec3 &accel);

        virtual glm::vec3 getVelocity() const;
        virtual void setVelocity(const glm::vec3 &vel);

        virtual glm::vec3 getPosition() const;
        virtual void setPosition(const glm::vec3 &pos);

        virtual float getMaxSpeed() const;
        virtual void setMaxSpeed(float newSpeed);

        virtual glm::vec2 getSize() const;
        virtual void setSize(const glm::vec2 &newSize);

        virtual glm::vec2 getHalfSpace() const;

        virtual const glm::vec3 getBulletPosition() const = 0;
        virtual std::vector<BulletPartical::Partical> getBullets() const { return std::vector<BulletPartical::Partical>(); };
        virtual int getID() const = 0;
        virtual bool isDead() const;

        virtual uint32_t getLives() const;

        Tempest::Rect getCollisionRect() const;

    protected:
        float layer;
        int entityID = -1;

        Tempest::Rect collisionRect;

        glm::vec4 colour = { 0.f, 0.f, 0.f, 1.0f };

        float speed = 10.f;

        virtual void onRender() = 0;
    };
}

#endif // !BASE_ENTITY_HDR

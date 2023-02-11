#include "BaseEntity.h"

namespace game
{
    BaseEntity::BaseEntity(int id) : layer(1.f), entityID(id)
    {
    }

    double BaseEntity::getAge() const 
    {
        //TODO: Might need to implement this.
        return 0;
    }

    glm::vec3 BaseEntity::getAcceleration() const
    {
        return collisionRect.acceleration;
    }

    void BaseEntity::setAcceleration(const glm::vec3& accel) 
    {
        collisionRect.acceleration = accel;
    }

    glm::vec3 BaseEntity::getVelocity() const 
    {
        return collisionRect.velocity;
    }

    void BaseEntity::setVelocity(const glm::vec3& vel) 
    {
        collisionRect.velocity = vel;
    }

    glm::vec3 BaseEntity::getPosition() const 
    {
        return collisionRect.position;
    }

    void BaseEntity::setPosition(const glm::vec3& pos) 
    {
        collisionRect.position = pos;
    }

    double BaseEntity::getMaxSpeed() const 
    {
        return speed;
    }

    void BaseEntity::setMaxSpeed(double speed) 
    {
        this->speed = speed;
    }

    glm::vec2 BaseEntity::getSize() const 
    {
        return collisionRect.size;
    }

    void BaseEntity::setSize(const glm::vec2& newSize) 
    {
        collisionRect.size = newSize;
        collisionRect.halfSpace.x = collisionRect.size.x / 2;
        collisionRect.halfSpace.y = collisionRect.size.y / 2;
    }

    glm::vec2 BaseEntity::getHalfSpace() const 
    {
        return collisionRect.halfSpace;
    }

    bool BaseEntity::isDead() const
    {
        return false;
    }

    uint32_t BaseEntity::getLives() const 
    {
        return 0;
    }

    Tempest::Rect BaseEntity::getCollisionRect() const 
    {
        return collisionRect;
    }
}
#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <Tempest.h>

#include <memory>

#include "BaseEntity.h"
#include "Bullet.h"


namespace 
{
    float LINEAR_DAMPING = 0.95f;
}

namespace game
{
    class Bullet;

    class Player : public BaseEntity
    {
        enum class CURRENT_STATE
        {
            DAMAGED,
            FLYING
        };
    public:
        Player(int id);

        virtual void init();
        void loadAssets();
        void onUpdate(Tempest::TimeStep ts);
        void onRender();

        void onImGuiRender();
        void reset();

        bool isDead() const;
        float getRotation() { return (collisionRect.velocity.y); }

        virtual const glm::vec3 getBulletPosition() const override;
        virtual int getID() const override;
    private:
        std::unique_ptr<Bullet> _bullet;

        int _lives = 7;

        CURRENT_STATE _currentState;
        Tempest::TimeStep _totalTime;
        Tempest::TimeStep _movementTime;
        float _invisibilityTime = 0.1f;

        Tempest::Rect testRect;
        //Test stuff

        Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;
        Tempest::ref<Tempest::Texture2D> _astroid;
        Tempest::ref<Tempest::SubTexture2D> _shipTexture;

        Tempest::ParticalProps _smokeParticalProps, _fireParticalProps;
        Tempest::ParticalSystem _particalSystem;

        float _time = 0.f;
        float _smokeInterval = 0.4f;
        float _smokeEmitTime = _smokeInterval;
    };
}

#endif // !PLAYER_HDR

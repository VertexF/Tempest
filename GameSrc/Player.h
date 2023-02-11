#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <Tempest.h>

#include <memory>

#include "BaseEntity.h"
#include "BulletParticles.h"

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

        float getRotation() { return (collisionRect.velocity.y); }

        virtual std::vector<BulletPartical::Partical> getBullets() const;
        virtual int getID() const override;

        virtual bool isDead() const override;
        virtual uint32_t getLives() const override;
    private:
        int _lives = 7;

        CURRENT_STATE _currentState;
        Tempest::TimeStep _totalTime;
        Tempest::TimeStep _movementTime;
        float _invisibilityTime = 0.1f;

        Tempest::Rect testRect;
        //Test stuff

        Tempest::ref<Tempest::Texture2D> _astroid;
        Tempest::ref<Tempest::SubTexture2D> _shipTexture;
        Tempest::scope<Tempest::SoundSource> _mySource;
        uint32_t _laserSoundBuffer = 0;

        Tempest::ParticalProps _smokeParticalProps, _fireParticalProps;
        Tempest::ParticalSystem _particalSystem;

        ParticalProps _bulletParticalProps;
        BulletPartical _bulletEmitter;

        float _time = 0.f;
        float _smokeInterval = 0.4f;
        float _smokeEmitTime = _smokeInterval;
    };
}

#endif // !PLAYER_HDR

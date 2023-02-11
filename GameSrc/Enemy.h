#ifndef ENEMY_HDR
#define ENEMY_HDR

#include <glm/glm.hpp>

#include "Global.h"
#include "BulletParticles.h"

namespace game
{
    class Enemy : public BaseEntity
    {
        enum class CURRENT_STATE 
        {
            DAMAGED,
            FLYING
        };
    public:
        Enemy(int id);

        virtual void init() override;

        void onRender();
        void onUpdate(Tempest::TimeStep timeStep);

        void spawn();

        void move(Tempest::TimeStep timeStep);
        void fire(Tempest::TimeStep timeStep);

        virtual const glm::vec3 getBulletPosition() const override;
        virtual std::vector<BulletPartical::Partical> getBullets() const;
        virtual int getID() const override;

        virtual bool isDead() const override;
    private:
        int _lives;

        CURRENT_STATE _currentState;
        Tempest::TimeStep _totalTime;
        Tempest::TimeStep _movementTime;
        float _invisibilityTime = 0.1f;

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

#endif // !ENEMY_HDR

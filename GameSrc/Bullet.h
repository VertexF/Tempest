#ifndef BULLET_HDR
#define BULLET_HDR

#include "Tempest/Core/TimeStep.h"
#include "BaseEntity.h"

#include <glm/glm.hpp>

namespace game 
{
    enum class BULLET_STATE 
    {
        READY,
        FIRE,
        RESET
    };

    class Bullet : public BaseEntity
    {
    public:
        Bullet(int id, bool isPlayer);

        void init() {}
        void onRender();
        void onUpdate(Tempest::TimeStep ts);

        void setColour(const glm::vec4& colour);

        virtual const glm::vec3 getBulletPosition() const override;
        virtual int getID() const override;
    private:
        BULLET_STATE _currentState;

        Tempest::TimeStep _totalTime;
        float lifeTime = 1.f;

        Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;
        Tempest::ref<Tempest::SubTexture2D> _bulletTexture;

        Tempest::ref<Tempest::SoundDevice> _soundDevice;
        Tempest::ref<Tempest::SoundBuffer> _soundBuffer;
        Tempest::ref<Tempest::SoundSource> _mySource;

        uint32_t _laserSoundBuffer = 0;
    };
}

#endif // !BULLET_HDR

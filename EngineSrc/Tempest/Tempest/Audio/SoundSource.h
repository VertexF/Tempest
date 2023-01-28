#ifndef SOUND_SOURCE_HDR
#define SOUND_SOURCE_HDR

#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <glm/glm.hpp>

namespace Tempest 
{
    class SoundSource 
    {
    public:
        SoundSource();
        ~SoundSource();

        void play(uint32_t slot);
    private:
        uint32_t _source = 0;
        float _pitch = 1.f;
        float _gain = 1.f;

        glm::vec3 _position = { 0, 0, 0 };
        glm::vec3 _velocity = { 0, 0, 0 };

        bool _loopSound = false;
        uint32_t _buffer = 0;

        int32_t _stateFlag;
    };
}

#endif //!SOUND_SOURCE_HDR
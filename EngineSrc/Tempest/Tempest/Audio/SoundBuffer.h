#ifndef SOUND_BUFFER_HDR
#define SOUND_BUFFER_HDR

#define AL_LIBTYPE_STATIC
#include <AL/al.h>

#include "Tempest/Core/Core.h"

namespace Tempest 
{
    class SoundBuffer 
    {
    public:
        SoundBuffer() = default;
        ~SoundBuffer() = default;

        virtual uint32_t addSoundEffect(const char* filename) = 0;
        virtual void removeSoundEffect(const ALuint& buffer) = 0;
    };
}

#endif // !SOUND_BUFFER_HDR

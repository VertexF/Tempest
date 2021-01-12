#ifndef SOUND_BUFFER_HDR
#define SOUND_BUFFER_HDR

#include <AL/al.h>

#include "Tempest/Core/Core.h"

namespace Tempest 
{
    class SoundBuffer 
    {
    public:
        ~SoundBuffer() = default;

        virtual uint32_t addSoundEffect(const char* filename) = 0;
        virtual void removeSoundEffect(const ALuint& buffer) = 0;

        static ref<SoundBuffer> create();
    };
}

#endif // !SOUND_BUFFER_HDR

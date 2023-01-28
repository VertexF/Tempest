#ifndef OPENAL_SOUND_BUFFER_HDR
#define OPENAL_SOUND_BUFFER_HDR

#include "SoundBuffer.h"

#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <vector>

namespace Tempest 
{
    class OpenALSoundBuffer : public SoundBuffer
    {
    public:
        OpenALSoundBuffer();
        virtual ~OpenALSoundBuffer();

        virtual uint32_t addSoundEffect(const char* filename) override;
        virtual void removeSoundEffect(const ALuint& buffer) override;
    private:
        std::vector<ALuint> _soundEffectBuffers;
    };
}

#endif // !OPENAL_SOUND_BUFFER_HDR

#ifndef AUDIO_HDR
#define AUDIO_HDR

#include "PreComp.h"

#include "OpenALSoundBuffer.h"
#include "OpenALSoundDevice.h"
#include "SoundSource.h"

namespace Tempest 
{
    struct Audio 
    {
        Audio();
        ~Audio() = default;

        uint32_t addSoundEffect(const std::string& filePath);
        void removeSoundEffect(uint32_t soundBuffer);
    private:

        Tempest::scope<Tempest::OpenALSoundDevice> _soundDevice;
        Tempest::scope<Tempest::OpenALSoundBuffer> _soundBuffer;
    };
}

#endif // !AUDIO_HDR

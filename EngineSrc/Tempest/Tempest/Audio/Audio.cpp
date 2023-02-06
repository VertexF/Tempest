#include "PreComp.h"
#include "Audio.h"

namespace Tempest 
{
    Audio::Audio()
    {
        _soundDevice = std::make_unique<OpenALSoundDevice>();
        _soundBuffer = std::make_unique<OpenALSoundBuffer>();
    }

    uint32_t Audio::addSoundEffect(const std::string& filePath)
    {
        return _soundBuffer->addSoundEffect(filePath.c_str());
    }

    void Audio::removeSoundEffect(uint32_t soundBuffer)
    {
        _soundBuffer->removeSoundEffect(soundBuffer);
    }
}
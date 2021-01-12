#include "PreComp.h"
#include "SoundBuffer.h"

#include "OpenALSoundBuffer.h"

namespace Tempest 
{
    ref<SoundBuffer> SoundBuffer::create() 
    {
        return std::make_shared<OpenALSoundBuffer>();
    }
}
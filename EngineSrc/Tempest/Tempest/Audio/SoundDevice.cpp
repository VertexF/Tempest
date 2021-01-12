#include "PreComp.h"
#include "SoundDevice.h"

#include "OpenALSoundDevice.h"

namespace Tempest 
{
    ref<SoundDevice> SoundDevice::create()
    { 
        return std::make_shared<OpenALSoundDevice>();
    }
}
#ifndef SOUND_DEVICE_HDR
#define SOUND_DEVICE_HDR

#include "Tempest/Core/Core.h"

namespace Tempest
{
    class SoundDevice 
    {
    public:
        SoundDevice() = default;
        virtual ~SoundDevice() = default;

        static ref<SoundDevice> create();
    private:
    };
}

#endif // !SOUND_DEVICE_HDR

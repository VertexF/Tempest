#ifndef OPENAL_SOUND_DEVICE_HDR
#define OPENAL_SOUND_DEVICE_HDR

#define AL_LIBTYPE_STATIC
#include <Al/alc.h>
#include <sndfile.h>

#include "SoundDevice.h"

namespace Tempest 
{
    class OpenALSoundDevice : public SoundDevice
    {
    public:
        OpenALSoundDevice();
        virtual ~OpenALSoundDevice();
    private:

        ALCdevice* _device;
        ALCcontext* _context;
    };
}

#endif // !OPENAL_SOUND_DEVICE_HDR

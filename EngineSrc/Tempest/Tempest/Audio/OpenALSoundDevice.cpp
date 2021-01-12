#include "PreComp.h"
#include "OpenALSoundDevice.h"

#include <al/al.h>

#include "Tempest/Core/Core.h"

namespace Tempest 
{
    OpenALSoundDevice::OpenALSoundDevice()
    {
        _device = alcOpenDevice(nullptr);
        TEMPEST_CORE_ASSERT(_device != nullptr, "Failed to find a sound device");

        _context = alcCreateContext(_device, nullptr);
        TEMPEST_CORE_ASSERT(_context != nullptr, "Failed to create sound context");

        if (alcMakeContextCurrent(_context) == false)
        {
            TEMPEST_CRITICAL("Failed to make sound context current.");
        }

        const ALCchar* name = nullptr;
        if (alcIsExtensionPresent(_device, "ALC_ENUMERATE_ALL_EXT"))
        {
            name = alcGetString(_device, ALC_ALL_DEVICES_SPECIFIER);
        }

        if (!name || alcGetError(_device) != AL_NO_ERROR)
        {
            name = alcGetString(_device, ALC_DEVICE_SPECIFIER);
        }

        TEMPEST_INFO("Opened {0}", name);
    }

    OpenALSoundDevice::~OpenALSoundDevice()
    {
        if (alcMakeContextCurrent(nullptr) == false)
        {
            TEMPEST_CRITICAL("failed to set context to nullptr");
        }

        alcDestroyContext(_context);
        TEMPEST_CORE_ASSERT(_context != nullptr, "failed to unset during close");

        if (alcCloseDevice(_device) == false)
        {
            TEMPEST_CRITICAL("failed to close sound device");
        }
    }
}
#include "PreComp.h"
#include "SoundSource.h"

#include <glm/gtc/type_ptr.hpp>

#include "Tempest/Core/Core.h"

namespace Tempest 
{
    SoundSource::SoundSource() 
    {
        alGenSources(1, &_source);

        if (_source == 0)
        {
            TEMPEST_CRITICAL("OpenAL could not create a sound source: {0}", alGetError());
        }

        alSourcef(_source, AL_PITCH, _pitch);
        alSourcef(_source, AL_GAIN, _gain);

        alSource3f(_source, AL_POSITION, _position.x, _position.y, _position.z);
        alSource3f(_source, AL_VELOCITY, _velocity.x, _velocity.y, _velocity.z);

        alSourcei(_source, AL_LOOPING, _loopSound);
        alSourcei(_source, AL_BUFFER, _buffer);
    }

    SoundSource::~SoundSource() 
    {
        alDeleteSources(1, &_source);
    }

    void SoundSource::play(uint32_t slot) 
    {
        alGetSourcei(_source, AL_SOURCE_STATE, &_stateFlag);
        if (slot != _buffer)
        {
            if (_stateFlag == AL_INITIAL || _stateFlag == AL_STOPPED)
            {
                _buffer = slot;
                alSourcei(_source, AL_BUFFER, (ALint)_buffer);
                alSourcePlay(_source);
            }
        }
        else 
        {
            alSourcePlay(_source);
        }
    }
}
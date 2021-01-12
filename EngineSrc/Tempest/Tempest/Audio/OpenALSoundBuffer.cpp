#include "PreComp.h"
#include "OpenALSoundBuffer.h"

#include <sndfile.h>
#include <inttypes.h>
#include <AL\alext.h>

namespace Tempest 
{
    OpenALSoundBuffer::OpenALSoundBuffer()
    {
        _soundEffectBuffers.clear();
    }

    OpenALSoundBuffer::~OpenALSoundBuffer()
    {
        alDeleteBuffers(_soundEffectBuffers.size(), _soundEffectBuffers.data());

        _soundEffectBuffers.clear();
    }

    uint32_t OpenALSoundBuffer::addSoundEffect(const char* filename)
    {
        ALenum err, format;
        ALuint buffer;
        SNDFILE* sndfile;
        SF_INFO sfinfo;
        short* membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;

        sfinfo.samplerate = 44;
        sfinfo.channels = 2;

        /* Open the audio file and check that it's usable. */
        sndfile = sf_open(filename, SFM_READ, &sfinfo);
        if (sndfile == nullptr)
        {
            const char* errorString = sf_strerror(sndfile);

            TEMPEST_CRITICAL("File name {0}", filename);
            TEMPEST_CRITICAL("Error string {0}", errorString);
            TEMPEST_CORE_ASSERT(false, "Could not open audio in");
        }

        if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
        {
            TEMPEST_CRITICAL("Bad sample count in {0} : {1}", filename, sfinfo.frames);
            sf_close(sndfile);
        }

        /* Get the sound format, and figure out the OpenAL format */
        format = AL_NONE;
        switch (sfinfo.channels)
        {
        case 1:
            format = AL_FORMAT_MONO16;
        break;
        case 2:
            format = AL_FORMAT_STEREO16;
        break;
        case 3:
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            {
                format = AL_FORMAT_BFORMAT2D_16;
            }
        break;
        case 4:
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            {
                format = AL_FORMAT_BFORMAT3D_16;
            }
        break;
        }

        if (format == AL_NONE)
        {
            TEMPEST_CRITICAL("Unsupported channel count: {0}", sfinfo.channels);
            sf_close(sndfile);
        }

        /* Decode the whole audio file to a buffer. */
        membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if (num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            TEMPEST_CRITICAL("Failed to read samples in {0} : {1}", filename, num_frames);
        }

        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        /* Buffer the audio data into a new buffer object, then free the data and
         * close the file.
         */
        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        /* Check if an error occured, and clean up if so. */
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            TEMPEST_CRITICAL("OpenAL Error: {0}", alGetString(err));
            if (buffer && alIsBuffer(buffer))
            {
                alDeleteBuffers(1, &buffer);
            }
        }

        _soundEffectBuffers.push_back(buffer);  // add to the list of known buffers

        return buffer;
    }

    void OpenALSoundBuffer::removeSoundEffect(const ALuint& buffer)
    {
        for (auto it = _soundEffectBuffers.begin(); it != _soundEffectBuffers.end(); ++it) 
        {
            if (*it == buffer)
            {
                alDeleteBuffers(1, &*it);
                it = _soundEffectBuffers.erase(it);
                return;
            }
        }
        
        TEMPEST_ERROR("Could not remove sound affect.");
    }
}
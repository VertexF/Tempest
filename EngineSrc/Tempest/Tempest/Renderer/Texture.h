#ifndef TEXTURE_HDR
#define TEXTURE_HDR

#include "PreComp.h"
#include "../Core.h"

namespace Tempest 
{
    class Texture 
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture 
    {
    public:
        virtual ~Texture2D() = default;
        static ref<Texture2D> create(const std::string &path);
    };
}

#endif // !TEXTURE_HDR
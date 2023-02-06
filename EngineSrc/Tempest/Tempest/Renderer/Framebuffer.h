#ifndef FRAMEBUFFER_HDR
#define FRAMEBUFFER_HDR

#include "Tempest/Core/Core.h"
#include <glm/gtc/type_ptr.hpp>

namespace Tempest 
{
    //Framebuffer properities.
    struct FramebufferSpec 
    {
        uint32_t width;
        uint32_t height;

        //FramebufferFormat = ...

        uint32_t sample = 1;
        bool swapChainTarget = false;
    };

    class Framebuffer 
    {
    public:
        virtual ~Framebuffer() = default;

        virtual const FramebufferSpec getFramebufferSpec() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual uint32_t getColourAttachmentRendererID() const = 0;

        static ref<Framebuffer> create(const FramebufferSpec& spec);
    };
}

#endif // !FRAMEBUFFER_HDR

#include "PreComp.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "Tempest/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Tempest 
{
    ref<Framebuffer> Framebuffer::create(const FramebufferSpec& spec) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLFramebuffer>(spec);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
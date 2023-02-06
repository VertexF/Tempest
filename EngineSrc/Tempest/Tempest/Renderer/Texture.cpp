#include "PreComp.h"
#include "Texture.h"

#include "Renderer.h"
#include "Tempest/Platform/OpenGL/OpenGLTexture.h"

namespace Tempest 
{
    ref<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLTexture2D>(path);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLTexture2D>(width, height);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height, int channel)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLTexture2D>(width, height, channel);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
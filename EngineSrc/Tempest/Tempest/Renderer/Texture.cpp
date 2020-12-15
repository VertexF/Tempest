#include "PreComp.h"
#include "Texture.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLTexture.h"

namespace Tempest 
{
    ref<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLTexture2D>(path);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}
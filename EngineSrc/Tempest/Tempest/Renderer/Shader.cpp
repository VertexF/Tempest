#include "PreComp.h"
#include "Shader.h"

#include "../Renderer/Renderer.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Tempest 
{
    ref<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }

    ref<Shader> Shader::create(const std::string& path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLShader>(path);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}
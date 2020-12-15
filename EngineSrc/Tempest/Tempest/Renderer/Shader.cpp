#include "PreComp.h"
#include "Shader.h"

#include "../Renderer/Renderer.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Tempest 
{
    Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}
#include "PreComp.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Tempest/Platform/OpenGL/OpenGLVertexArray.h"

namespace Tempest 
{
    ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
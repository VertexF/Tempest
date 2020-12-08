#include "PreComp.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Tempest 
{
    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::OPENGL:
            return new OpenGLVertexArray();
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}
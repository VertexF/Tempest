#include "PreComp.h"
#include "Buffer.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

namespace Tempest 
{
    VertexBuffer *VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI()) 
        {
        case RendererAPI::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::OPENGL:
            return new OpenGLVertexBuffer(vertices, size);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t *indices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::NONE:
            TEMPEST_ERROR("Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::OPENGL:
            return new OpenGLIndexBuffer(indices, size);
            break;
        }

        TEMPEST_ERROR("Unknown RendererAPI!");
        return nullptr;
    }
}
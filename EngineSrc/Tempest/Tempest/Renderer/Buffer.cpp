#include "PreComp.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Tempest/Core/Core.h"
#include "Tempest/Platform/OpenGL/OpenGLBuffer.h"

namespace Tempest 
{
    ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI()) 
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<IndexBuffer> IndexBuffer::create(uint32_t *indices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::NONE:
            TEMPEST_CORE_ASSERT(false, "Renderer Type None is not supported!");
            return nullptr;
            break;
        case RendererAPI::API::OPENGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, size);
            break;
        }

        TEMPEST_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
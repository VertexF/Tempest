#ifndef OPENGL_RENDERER_API_HDR
#define OPENGL_RENDERER_API_HDR

#include "Tempest/Core/Core.h"
#include "Tempest/Renderer/RendererAPI.h"

namespace Tempest 
{
    class OpenGLRendererAPI : public RendererAPI 
    {
        virtual void init() override;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        virtual void clear() override;
        virtual void setClearColour(const glm::vec4& colour) override;

        virtual void drawIndexed(const ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
    };
}

#endif // !OPENGL_RENDERER_API_HDR

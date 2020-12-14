#ifndef OPENGL_RENDERER_API_HDR
#define OPENGL_RENDERER_API_HDR

#include "../Renderer/RendererAPI.h"

namespace Tempest 
{
    class OpenGLRendererAPI : public RendererAPI 
    {
        virtual void clear() override;
        virtual void setClearColour(const glm::vec4& colour) override;

        virtual void drawIndexed(const ref<VertexArray>& vertexArray) override;
    };
}

#endif // !OPENGL_RENDERER_API_HDR

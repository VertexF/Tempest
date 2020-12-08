#ifndef RENDERER_API_HDR
#define RENDERER_API_HDR

#include <glm/glm.hpp>
#include "PreComp.h"

#include "VertexArray.h"

namespace Tempest 
{
    class RendererAPI 
    {
    public:
        enum class API 
        {
            NONE = 0, 
            OPENGL
        };
    public:
        virtual void clear() = 0;
        virtual void setClearColour(const glm::vec4 &colour) = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

        inline static API getAPI() { return _API; }
    private:
        static API _API;
    };
}

#endif // !RENDERER_API_HDR

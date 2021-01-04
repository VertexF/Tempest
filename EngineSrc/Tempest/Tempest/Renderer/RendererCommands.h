#ifndef RENDERER_COMMANDS_HDR
#define RENDERER_COMMANDS_HDR

#include "PreComp.h"

#include <glm/glm.hpp>
#include "RendererAPI.h"

#include "Tempest/Core/Core.h"

namespace Tempest 
{
    class RendererCommands 
    {
    public:
        static void init() 
        {
            _rendererAPI->init();
        }

        static void setClearColour(const glm::vec4 &colour) 
        {
            _rendererAPI->setClearColour(colour);
        }

        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            _rendererAPI->setViewport(x, y, width, height);
        }

        static void clear() 
        {
            _rendererAPI->clear();
        }

        static void drawIndexed(const ref<VertexArray> &vertexArray, uint32_t indexCount = 0) 
        {
            _rendererAPI->drawIndexed(vertexArray, indexCount);
        }
    private:
        static RendererAPI *_rendererAPI;
    };
}

#endif // !RENDERER_COMMANDS_HDR

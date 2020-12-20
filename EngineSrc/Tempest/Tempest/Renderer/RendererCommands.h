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
        inline static void init() 
        {
            _rendererAPI->init();
        }

        inline static void setClearColour(const glm::vec4 &colour) 
        {
            _rendererAPI->setClearColour(colour);
        }

        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            _rendererAPI->setViewport(x, y, width, height);
        }

        inline static void clear() 
        {
            _rendererAPI->clear();
        }

        inline static void drawIndexed(const ref<VertexArray> &vertexArray) 
        {
            _rendererAPI->drawIndexed(vertexArray);
        }
    private:
        static RendererAPI *_rendererAPI;
    };
}

#endif // !RENDERER_COMMANDS_HDR

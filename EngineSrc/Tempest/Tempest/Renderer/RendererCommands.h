#ifndef RENDERER_COMMANDS_HDR
#define RENDERER_COMMANDS_HDR

#include "PreComp.h"

#include <glm/glm.hpp>
#include "RendererAPI.h"

#include "../Core.h"

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

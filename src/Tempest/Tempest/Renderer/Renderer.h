#ifndef RENDERER_HDR
#define RENDERER_HDR

#include "RendererCommands.h"
#include "RendererAPI.h"

namespace Tempest 
{
    class Renderer 
    {
    public:
        static void beginScene();
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    };
}

#endif // !RENDERER_HDR

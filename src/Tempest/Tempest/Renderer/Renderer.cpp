#include "PreComp.h"
#include "Renderer.h"

namespace Tempest 
{
    void Renderer::beginScene()
    {
        
    }

    void Renderer::endScene()
    {
        
    }

    void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->bind();
        RendererCommands::drawIndexed(vertexArray);
    }
}
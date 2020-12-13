#include "PreComp.h"
#include "Renderer.h"

namespace Tempest 
{
    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        _sceneData->_viewProjectMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene()
    {
        
    }

    void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4x4 &transform)
    {
        shader->bind();
        shader->setMatrix4Uniform("uViewProjectmatrix", _sceneData->_viewProjectMatrix);
        shader->setMatrix4Uniform("uModelMatrix", transform);

        vertexArray->bind();
        RendererCommands::drawIndexed(vertexArray);
    }
}
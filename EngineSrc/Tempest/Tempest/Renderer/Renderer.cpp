#include "PreComp.h"
#include "Renderer.h"

#include "Tempest/Platform/OpenGL/OpenGLShader.h"

namespace Tempest 
{
    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;
    
    void Renderer::init()
    {
        RendererCommands::init();
    }

    void Renderer::onResizeEvent(uint32_t width, uint32_t height) 
    {
        RendererCommands::setViewport(0, 0, width, height);
    }

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        _sceneData->_viewProjectMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene()
    {
        
    }

    void Renderer::submit(const ref<VertexArray>& vertexArray, const ref<Shader>& shader, const glm::mat4x4 &transform)
    {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setMatrix4Uniform("uViewProjectmatrix", _sceneData->_viewProjectMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setMatrix4Uniform("uModelMatrix", transform);

        vertexArray->bind();
        RendererCommands::drawIndexed(vertexArray);
    }
}
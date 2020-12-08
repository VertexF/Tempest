#include "PreComp.h"
#include "OpenGLRendererAPI.h"

#include <gl/glew.h>

namespace Tempest
{
    void OpenGLRendererAPI::clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::setClearColour(const glm::vec4& colour) 
    {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}
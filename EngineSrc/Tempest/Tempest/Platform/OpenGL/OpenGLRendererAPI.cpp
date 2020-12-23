#include "PreComp.h"
#include "OpenGLRendererAPI.h"

#include <gl/glew.h>

namespace Tempest
{
    void OpenGLRendererAPI::init() 
    {
        TEMPEST_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::setClearColour(const glm::vec4& colour) 
    {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    void OpenGLRendererAPI::drawIndexed(const ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}
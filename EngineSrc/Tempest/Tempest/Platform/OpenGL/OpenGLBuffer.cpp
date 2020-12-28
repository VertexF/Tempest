#include "PreComp.h"
#include "OpenGLBuffer.h"

#include <gl/glew.h>

namespace Tempest
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        TEMPEST_PROFILE_FUNCTION();

        glCreateBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        TEMPEST_PROFILE_FUNCTION();
        glCreateBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteBuffers(1, &_vertexBuffer);
    }

    void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void OpenGLVertexBuffer::bind() const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) :
        _count(count)
    {
        TEMPEST_PROFILE_FUNCTION();
        glCreateBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteBuffers(1, &_indexBuffer);
    }

    void OpenGLIndexBuffer::setData()
    {
    }

    void OpenGLIndexBuffer::bind() const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
#include "PreComp.h"
#include "OpenGLVertexArray.h"

#include <gl/glew.h>

namespace Tempest 
{
    static GLenum shaderDataTypeToOpenGL(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::FLOAT: return GL_FLOAT; break;
        case ShaderDataType::FLOAT2: return GL_FLOAT; break;
        case ShaderDataType::FLOAT3: return GL_FLOAT; break;
        case ShaderDataType::FLOAT4: return GL_FLOAT; break;

        case ShaderDataType::INT: return GL_INT; break;
        case ShaderDataType::INT2: return GL_INT; break;
        case ShaderDataType::INT3: return GL_INT; break;
        case ShaderDataType::INT4: return GL_INT; break;

        case ShaderDataType::MAT3x3: return GL_FLOAT; break;
        case ShaderDataType::MAT4x4: return GL_FLOAT; break;

        case ShaderDataType::BOOL: return GL_BOOL; break;
        }

        TEMPEST_ERROR("Shader data type not supported!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() 
    {
        glGenVertexArrays(1, &_vertexArray);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &_vertexArray);
    }

    void OpenGLVertexArray::bind() const 
    {
        glBindVertexArray(_vertexArray);
    }

    void OpenGLVertexArray::unbind() const 
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const ref<VertexBuffer>& vertexBuffer) 
    {
        if (vertexBuffer->getLayout().getElements().empty())
        {
            TEMPEST_ERROR("Error: The layout is empty. Did you add the vertex buffer before setting the layout of the vertex buffer?");
        }
        else
        {

            glBindVertexArray(_vertexArray);
            vertexBuffer->bind();

            uint32_t index = 0;
            for (const auto& element : vertexBuffer->getLayout())
            {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index,
                    element.getCompomentCount(),
                    shaderDataTypeToOpenGL(element.type),
                    element.normalised ? GL_TRUE : GL_FALSE,
                    vertexBuffer->getLayout().getStride(),
                    reinterpret_cast<const void*>((intptr_t)element.offset));
                index++;
            }

            _vertexBuffers.push_back(vertexBuffer);
        }
    }

    void OpenGLVertexArray::setIndexBuffer(const ref<IndexBuffer>& indexBuffer) 
    {
        glBindVertexArray(_vertexArray);
        indexBuffer->bind();

        _indexBuffer = indexBuffer;
    }
}
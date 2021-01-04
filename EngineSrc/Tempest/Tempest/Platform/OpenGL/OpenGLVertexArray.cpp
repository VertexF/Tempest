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
        TEMPEST_PROFILE_FUNCTION();
        glGenVertexArrays(1, &_vertexArray);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        TEMPEST_PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &_vertexArray);
    }

    void OpenGLVertexArray::bind() const 
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindVertexArray(_vertexArray);
    }

    void OpenGLVertexArray::unbind() const 
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const ref<VertexBuffer>& vertexBuffer) 
    {
        TEMPEST_PROFILE_FUNCTION();

        TEMPEST_CORE_ASSERT(vertexBuffer->getLayout().getElements().empty() == false, 
                            "Error: The layout is empty. Did you add the vertex buffer before setting the layout of the vertex buffer?");

        glBindVertexArray(_vertexArray);
        vertexBuffer->bind();

        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(_vertexBufferIndex);
            if (shaderDataTypeToOpenGL(element.type) == GL_INT)
            {
                glVertexAttribIPointer(_vertexBufferIndex,
                    element.getCompomentCount(),
                    shaderDataTypeToOpenGL(element.type),
                    layout.getStride(),
                    reinterpret_cast<const void*>((intptr_t)element.offset));
            }
            else 
            {
                glVertexAttribPointer(_vertexBufferIndex,
                    element.getCompomentCount(),
                    shaderDataTypeToOpenGL(element.type),
                    element.normalised ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    reinterpret_cast<const void*>((intptr_t)element.offset));
            }
            _vertexBufferIndex++;
        }

        _vertexBuffers.push_back(vertexBuffer);

    }

    void OpenGLVertexArray::setIndexBuffer(const ref<IndexBuffer>& indexBuffer) 
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindVertexArray(_vertexArray);
        indexBuffer->bind();

        _indexBuffer = indexBuffer;
    }
}
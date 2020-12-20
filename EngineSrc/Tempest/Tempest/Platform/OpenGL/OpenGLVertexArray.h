#ifndef OPENGL_VERTEX_ARRAY_HDR
#define OPENGL_VERTEX_ARRAY_HDR

#include "PreComp.h"
#include "Tempest/Renderer/VertexArray.h"
#include "Tempest/Core/Core.h"

namespace Tempest 
{
    class OpenGLVertexArray : public VertexArray 
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const ref<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const ref<IndexBuffer>& indexBuffer) override;

        virtual inline const std::vector<ref<VertexBuffer>>& getVertexBuffers() const override { return _vertexBuffers; }
        virtual inline ref<IndexBuffer> getIndexBuffer() const override { return _indexBuffer; }
    private:
        std::vector<ref<VertexBuffer>> _vertexBuffers;
        ref<IndexBuffer> _indexBuffer;
        uint32_t _vertexArray;
    };
}

#endif // !OPENGL_VERTEX_ARRAY_HDR

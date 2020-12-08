#ifndef OPENGL_VERTEX_ARRAY_HDR
#define OPENGL_VERTEX_ARRAY_HDR

#include "PreComp.h"
#include "../Renderer/VertexArray.h"

namespace Tempest 
{
    class OpenGLVertexArray : public VertexArray 
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return _vertexBuffers; }
        virtual inline std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return _indexBuffer; }
    private:
        std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
        std::shared_ptr<IndexBuffer> _indexBuffer;
        uint32_t _vertexArray;
    };
}

#endif // !OPENGL_VERTEX_ARRAY_HDR

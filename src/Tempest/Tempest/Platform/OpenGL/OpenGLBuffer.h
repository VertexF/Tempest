#ifndef OPENGL_BUFFER_HDR
#define OPENGL_BUFFER_HDR

#include "../Renderer/Buffer.h"

namespace Tempest 
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void setData() override;

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void setLayout(const BufferLayout& bufferLayout) override { _bufferLayout = bufferLayout; }
        virtual const BufferLayout getLayout() const override { return _bufferLayout; }

    private:
        uint32_t _vertexBuffer;
        BufferLayout _bufferLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t*indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void setData() override;

        virtual uint32_t getCount() const override { return _count; }

        virtual void bind() const override;
        virtual void unbind() const override;
    private:
        uint32_t _indexBuffer;
        uint32_t _count;
    };
}

#endif // !OPENGL_BUFFER_HDR

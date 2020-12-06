#ifndef BUFFER_HDR
#define BUFFER_HDR

namespace Tempest
{
    class VertexBuffer 
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void setData() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(float *vertices, uint32_t size);
    };

    class IndexBuffer 
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void setData() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* indices, uint32_t size);
    };
}

#endif // !BUFFER_HDR

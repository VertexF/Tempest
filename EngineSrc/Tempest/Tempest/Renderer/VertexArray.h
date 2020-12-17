#ifndef VERTEX_ARRAY_HDR
#define VERTEX_ARRAY_HDR

#include "PreComp.h"

#include "Buffer.h"
#include "../Core.h"

namespace Tempest 
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const ref<VertexBuffer> &vertexBuffer) = 0;
        virtual void setIndexBuffer(const ref<IndexBuffer> &indexBuffer) = 0;
        
        virtual const std::vector<ref<VertexBuffer>> &getVertexBuffers() const = 0;
        virtual ref<IndexBuffer> getIndexBuffer() const = 0;

        static ref<VertexArray> create();
    };
}

#endif //! VERTEX_ARRAY_HDR
#ifndef BUFFER_HDR
#define BUFFER_HDR

#include "../Core.h"

namespace Tempest
{
    enum class ShaderDataType
    {
        None = 0,
        FLOAT, FLOAT2, FLOAT3, FLOAT4,
        MAT3x3, MAT4x4,
        INT, INT2, INT3, INT4,
        BOOL
    };

    //Works out the size
    static uint32_t shaderDataTypeSize(ShaderDataType type) 
    {
        switch (type) 
        {
        case ShaderDataType::FLOAT: return 4; break;
        case ShaderDataType::FLOAT2: return 4 * 2; break;
        case ShaderDataType::FLOAT3: return 4 * 3; break;
        case ShaderDataType::FLOAT4: return 4 * 4; break;

        case ShaderDataType::INT: return 4; break;
        case ShaderDataType::INT2: return 4 * 2; break;
        case ShaderDataType::INT3: return 4 * 3; break;
        case ShaderDataType::INT4: return 4 * 4; break;

        case ShaderDataType::MAT3x3: return 4 * 3 * 3; break;
        case ShaderDataType::MAT4x4: return 4 * 4 * 4; break;

        case ShaderDataType::BOOL: return 1; break;
        }

        TEMPEST_ERROR("Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement
    {
        std::string name;
        uint32_t offset;
        uint32_t size;
        bool normalised;
        ShaderDataType type;

        BufferElement(ShaderDataType type, const std::string& name, bool normalised = false) :
            name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalised(normalised)
        {
        }

        uint32_t getCompomentCount() const
        {
            switch (type)
            {
            case ShaderDataType::FLOAT: return 1; break;
            case ShaderDataType::FLOAT2: return 2; break;
            case ShaderDataType::FLOAT3: return 3; break;
            case ShaderDataType::FLOAT4: return 4; break;

            case ShaderDataType::INT: return 1; break;
            case ShaderDataType::INT2: return 2; break;
            case ShaderDataType::INT3: return 3; break;
            case ShaderDataType::INT4: return 4 ; break;

            case ShaderDataType::MAT3x3: return 3 * 3; break;
            case ShaderDataType::MAT4x4: return 4 * 4; break;

            case ShaderDataType::BOOL: return 1; break;
            }

            TEMPEST_ERROR("Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement> &element) 
            : _bufferElements(element)
        {
            calculateOffsetAndStride();
        }

        std::vector<BufferElement>::iterator begin() { return _bufferElements.begin(); }
        std::vector<BufferElement>::iterator end() { return _bufferElements.end(); }

        std::vector<BufferElement>::const_iterator begin() const { return _bufferElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return _bufferElements.end(); }

        inline uint32_t getStride() const { return _stride; }
        inline const std::vector<BufferElement>& getElements() const { return _bufferElements; }
    private:
        void calculateOffsetAndStride() 
        {
            uint32_t offset = 0;
            _stride = 0;
            for (auto &element : _bufferElements)
            {
                element.offset = offset;
                offset += element.size;
                _stride += element.size;
            }
        }
    private:
        std::vector<BufferElement> _bufferElements;
        uint32_t _stride;
    };

    class VertexBuffer 
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void setData() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setLayout(const BufferLayout &bufferLayout) = 0; 
        virtual const BufferLayout getLayout() const = 0;

        static ref<VertexBuffer> create(float *vertices, uint32_t size);
    };

    class IndexBuffer 
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void setData() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static ref<IndexBuffer> create(uint32_t* indices, uint32_t size);
    };
}

#endif // !BUFFER_HDR

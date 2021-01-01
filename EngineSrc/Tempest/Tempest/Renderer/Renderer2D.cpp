#include "PreComp.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Tempest/Renderer/RendererCommands.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tempest 
{
    // This needs to be the same layout.
    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec4 colour;
        glm::vec2 texCoord;
        float tilingFactor;
        int textureIndex;
    };

    struct Renderer2DData 
    {
        static const uint32_t maxQuads = 20000;
        static const uint32_t maxVertices = maxQuads * 4;
        static const uint32_t maxIndices = maxQuads * 6;
        static const uint32_t maxTextureSlots = 32;

        ref<VertexArray> squareVA;
        ref<VertexBuffer> quadBuffer;
        ref<Shader> textureShader;
        ref<Texture2D> whiteTexture;

        uint32_t quadIndexCount = 0;
        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;

        std::array<ref<Texture2D>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 1;
        //Texture slot 0 is the white 1 by 1 texture we have at the beginning.

        glm::vec4 quadVertexPositions[4];

        Renderer2D::Statistics stats;
    };

    static Renderer2DData renderer2DData;

    void Renderer2D::init() 
    {
        TEMPEST_PROFILE_FUNCTION();

        renderer2DData.squareVA = VertexArray::create();
        renderer2DData.quadBuffer = VertexBuffer::create(Renderer2DData::maxVertices * sizeof(QuadVertex));

        BufferLayout layoutSquare = {
            { ShaderDataType::FLOAT3, "position" },
            { ShaderDataType::FLOAT4, "colour" },
            { ShaderDataType::FLOAT2, "texCoord" },
            { ShaderDataType::FLOAT, "tilingFactor" },
            { ShaderDataType::INT,  "texIndex"}
        };
        renderer2DData.quadBuffer->setLayout(layoutSquare);
        renderer2DData.squareVA->addVertexBuffer(renderer2DData.quadBuffer);

        renderer2DData.quadVertexBufferBase = new QuadVertex[Renderer2DData::maxVertices];

        uint32_t* quadIndices = new uint32_t[Renderer2DData::maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2DData::maxIndices; i += 6) 
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        ref<IndexBuffer> quadIB;
        quadIB = IndexBuffer::create(quadIndices, Renderer2DData::maxIndices);
        renderer2DData.squareVA->setIndexBuffer(quadIB);

        delete[] quadIndices;

        renderer2DData.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xFFFFFFFF;
        renderer2DData.whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        int samplers[Renderer2DData::maxTextureSlots];
        for (int i = 0; i < Renderer2DData::maxTextureSlots; ++i)
        {
            samplers[i] = i;
        }

        renderer2DData.textureShader = Shader::create("Assets/Shaders/Texture.glsl");
        renderer2DData.textureShader->bind();
        renderer2DData.textureShader->setIntArray("uTexture", renderer2DData.maxTextureSlots, samplers);

        renderer2DData.textureSlots[0] = renderer2DData.whiteTexture;

        renderer2DData.quadVertexPositions[0] = { -0.5f, -0.5f, 0.f, 1.f };
        renderer2DData.quadVertexPositions[1] = { 0.5f, -0.5f, 0.f, 1.f };
        renderer2DData.quadVertexPositions[2] = { 0.5f,  0.5f, 0.f, 1.f };
        renderer2DData.quadVertexPositions[3] = { -0.5f,  0.5f, 0.f, 1.f };
    }

    void Renderer2D::shutdown() 
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData.textureShader->bind();
        renderer2DData.textureShader->setMatrix4("uViewProjectmatrix", camera.getViewProjectionMatrix());

        renderer2DData.quadIndexCount = 0;
        renderer2DData.quadVertexBufferPtr = renderer2DData.quadVertexBufferBase;

        renderer2DData.textureSlotIndex = 1;
    }

    void Renderer2D::flush() 
    {
        TEMPEST_PROFILE_FUNCTION();

        for (uint32_t i = 0; i < renderer2DData.textureSlotIndex; ++i) 
        {
            renderer2DData.textureSlots[i]->bind(i);
        }

        RendererCommands::drawIndexed(renderer2DData.squareVA, renderer2DData.quadIndexCount);

        renderer2DData.stats.drawCalls++;
    }

    void Renderer2D::endScene() 
    {
        TEMPEST_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)renderer2DData.quadVertexBufferPtr - (uint8_t*)renderer2DData.quadVertexBufferBase;
        renderer2DData.quadBuffer->setData(renderer2DData.quadVertexBufferBase, dataSize);

        flush();
    }

    void Renderer2D::flushAndReset()
    {
        endScene();

        renderer2DData.quadIndexCount = 0;
        renderer2DData.quadVertexBufferPtr = renderer2DData.quadVertexBufferBase;

        renderer2DData.textureSlotIndex = 1;
    }

    //Primitive
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, colour);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        TEMPEST_PROFILE_FUNCTION();

        if (renderer2DData.quadIndexCount >= Renderer2DData::maxIndices)
        {
            flushAndReset();
        }

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) *
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 1.f });

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[0];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[1];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[2];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[3];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadIndexCount += 6;

        renderer2DData.stats.quadCount++;
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, texture, tileFactor, tint);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        TEMPEST_PROFILE_FUNCTION();

        //Temp
        constexpr float x = 2.f;
        constexpr float y = 3.f;
        constexpr float sheetWidth = 2560.f;
        constexpr float sheetHeight = 1664.f;
        constexpr float spriteWidth = 128.f; 
        constexpr float spriteHeight = 128.f;

        constexpr glm::vec2 textureCoords[] = { 
            { (x * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight },
            { ((x + 1) * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight },
            { ((x + 1) * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight },
            { (x * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight } };

        if (renderer2DData.quadIndexCount >= Renderer2DData::maxIndices)
        {
            flushAndReset();
        }

        int textureIndex = 0;

        for (uint32_t i = 1; i < renderer2DData.textureSlotIndex; ++i)
        {
            if (*renderer2DData.textureSlots[i].get() == *texture.get())
            {
                textureIndex = i;
            }
        }

        if (textureIndex == 0)
        {
            textureIndex = renderer2DData.textureSlotIndex;
            renderer2DData.textureSlots[renderer2DData.textureSlotIndex] = texture;
            renderer2DData.textureSlotIndex++;
        }

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) *
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 1.f });

        for (uint32_t i = 0; i < 4; ++i) 
        {
            renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[i];
            renderer2DData.quadVertexBufferPtr->colour = tint;
            renderer2DData.quadVertexBufferPtr->texCoord = textureCoords[i];
            renderer2DData.quadVertexBufferPtr->tilingFactor = tileFactor;
            renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
            renderer2DData.quadVertexBufferPtr++;
        }

        renderer2DData.quadIndexCount += 6;

        renderer2DData.stats.quadCount++;
    }

    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& colour)
    {
        drawRotatedQuad(glm::vec3(position.x, position.y, 0.f), size, rotation, colour);
    }

    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& colour)
    {
        TEMPEST_PROFILE_FUNCTION();

        if (renderer2DData.quadIndexCount >= Renderer2DData::maxIndices)
        {
            flushAndReset();
        }

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) *
                                glm::rotate(glm::mat4x4(1.f), glm::radians(rotation), { 0.f, 0.f, 1.f }) *
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 1.f });

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[0];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[1];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[2];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[3];
        renderer2DData.quadVertexBufferPtr->colour = colour;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = 1.f;
        renderer2DData.quadVertexBufferPtr->textureIndex = 0;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadIndexCount += 6;

        renderer2DData.stats.quadCount++;
    }

    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        drawRotatedQuad(glm::vec3(position.x, position.y, 0.f), size, rotation, texture, tileFactor, tint);
    }

    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        TEMPEST_PROFILE_FUNCTION();

        if (renderer2DData.quadIndexCount >= Renderer2DData::maxIndices)
        {
            flushAndReset();
        }

        int textureIndex = 0;

        for (uint32_t i = 1; i < renderer2DData.textureSlotIndex; ++i)
        {
            if (*renderer2DData.textureSlots[i].get() == *texture.get())
            {
                textureIndex = i;
            }
        }

        if (textureIndex == 0)
        {
            textureIndex = renderer2DData.textureSlotIndex;
            renderer2DData.textureSlots[renderer2DData.textureSlotIndex] = texture;
            renderer2DData.textureSlotIndex++;
        }

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * 
                                glm::rotate(glm::mat4x4(1.f), glm::radians(rotation), { 0.f, 0.f, 1.f }) *
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 1.f });

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[0];
        renderer2DData.quadVertexBufferPtr->colour = tint;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = tileFactor;
        renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position =  transform * renderer2DData.quadVertexPositions[1];
        renderer2DData.quadVertexBufferPtr->colour = tint;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 0.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = tileFactor;
        renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[2];
        renderer2DData.quadVertexBufferPtr->colour = tint;
        renderer2DData.quadVertexBufferPtr->texCoord = { 1.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = tileFactor;
        renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[3];
        renderer2DData.quadVertexBufferPtr->colour = tint;
        renderer2DData.quadVertexBufferPtr->texCoord = { 0.f, 1.f };
        renderer2DData.quadVertexBufferPtr->tilingFactor = tileFactor;
        renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
        renderer2DData.quadVertexBufferPtr++;

        renderer2DData.quadIndexCount += 6;

        renderer2DData.stats.quadCount++;
    }

    Renderer2D::Statistics Renderer2D::getStats() 
    {
        return renderer2DData.stats;
    }

    void Renderer2D::resetStats()
    {
        memset(&renderer2DData.stats, 0, sizeof(Renderer2D::Statistics));
    }
}
#include "PreComp.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Tempest/Renderer/RendererCommands.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tempest 
{
    struct Renderer2DData 
    {
        const uint32_t maxQuads = 10000;
        const uint32_t maxVertices = maxQuads * 4;
        const uint32_t maxIndices = maxQuads * 6;

        ref<VertexArray> squareVA;
        ref<Shader> textureShader;
        ref<Texture> whiteTexture;

        uint32_t quadIndexCount = 0;
    };

    static Renderer2DData renderer2DData;

    struct QuadVertex 
    {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec4 colour;
    };

    void Renderer2D::init() 
    {
        TEMPEST_PROFILE_FUNCTION();

        renderer2DData.squareVA = VertexArray::create();

        ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(sizeof(renderer2DData.maxVertices * sizeof(QuadVertex)));

        BufferLayout layoutSquare = {
            { ShaderDataType::FLOAT3, "position" },
            { ShaderDataType::FLOAT4, "colour" },
            { ShaderDataType::FLOAT2, "texCoord" }
        };

        squareVB->setLayout(layoutSquare);
        renderer2DData.squareVA->addVertexBuffer(squareVB);

        uint32_t* quadIndices = new uint32_t[renderer2DData.maxIndices];
        ref<IndexBuffer> quadIB;
        quadIB = IndexBuffer::create(quadIndices, renderer2DData.maxIndices);
        renderer2DData.squareVA->setIndexBuffer(quadIB);

        delete[] quadIndices;

        renderer2DData.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xFFFFFFFF;
        renderer2DData.whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        renderer2DData.textureShader = Shader::create("Assets/Shaders/Texture.glsl");

        renderer2DData.textureShader->bind();
        renderer2DData.textureShader->setInt("uTexture", 0);
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
    }

    void Renderer2D::endScene() 
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    //Primitive
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, colour);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData.textureShader->setVec4("uColour", colour);
        renderer2DData.textureShader->setFloat("uTileFactor", 1.f);
        renderer2DData.whiteTexture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * glm::scale(glm::mat4x4(1.f), {size.x, size.y, 0.f});
        renderer2DData.textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData.squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData.squareVA);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, texture, tileFactor, tint);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData.textureShader->setVec4("uColour", tint);
        renderer2DData.textureShader->setFloat("uTileFactor", tileFactor);
        texture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * glm::scale(glm::mat4x4(1.f), { size.x, size.y, 0.f });
        renderer2DData.textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData.squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData.squareVA);
        texture->unbind();
    }

    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& colour)
    {
        drawRotatedQuad(glm::vec3(position.x, position.y, 0.f), size, rotation, colour);
    }

    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& colour)
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData.textureShader->setVec4("uColour", colour);
        renderer2DData.textureShader->setFloat("uTileFactor", 1.f);
        renderer2DData.whiteTexture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * 
                                glm::rotate(glm::mat4x4(1.f), rotation, { 0.f, 0.f, 1.f }) * 
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 0.f });
        renderer2DData.textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData.squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData.squareVA);
    }

    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        drawRotatedQuad(glm::vec3(position.x, position.y, 0.f), size, rotation, texture, tileFactor, tint);
    }

    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor, const glm::vec4& tint)
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData.textureShader->setVec4("uColour", tint);
        renderer2DData.textureShader->setFloat("uTileFactor", tileFactor);
        texture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * 
                                glm::rotate(glm::mat4x4(1.f), rotation, { 0.f, 0.f, 1.f }) * 
                                glm::scale(glm::mat4x4(1.f), { size.x, size.y, 0.f });
        renderer2DData.textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData.squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData.squareVA);
        texture->unbind();
    }
}
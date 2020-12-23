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
        ref<VertexArray> squareVA;
        ref<Shader> textureShader;
        ref<Texture> whiteTexture;
    };

    static Renderer2DData* renderer2DData;

    void Renderer2D::init() 
    {
        TEMPEST_PROFILE_FUNCTION();

        renderer2DData = new Renderer2DData();

        renderer2DData->squareVA = VertexArray::create();

        float squareVerts[5 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 0.f, 0.f,
             0.5f, -0.5f, 0.0f, 1.f, 0.f,
             0.5f,  0.5f, 0.0f, 1.f, 1.f,
            -0.5f,  0.5f, 0.0f, 0.f, 1.f
        };

        ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVerts, sizeof(squareVerts));


        BufferLayout layoutSquare = {
            { ShaderDataType::FLOAT3, "position" },
            { ShaderDataType::FLOAT2, "texCoord" }
        };

        squareVB->setLayout(layoutSquare);
        renderer2DData->squareVA->addVertexBuffer(squareVB);

        uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
        ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::create(indices2, sizeof(indices2) / sizeof(uint32_t));
        renderer2DData->squareVA->setIndexBuffer(squareIB);

        renderer2DData->whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xFFFFFFFF;
        renderer2DData->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        renderer2DData->textureShader = Shader::create("Assets/Shaders/Texture.glsl");

        renderer2DData->textureShader->bind();
        renderer2DData->textureShader->setInt("uTexture", 0);
    }

    void Renderer2D::shutdown() 
    {
        TEMPEST_PROFILE_FUNCTION();
        delete renderer2DData;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData->textureShader->bind();
        renderer2DData->textureShader->setMatrix4("uViewProjectmatrix", camera.getViewProjectionMatrix());
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
        renderer2DData->textureShader->setVec4("uColour", colour);
        renderer2DData->whiteTexture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * glm::scale(glm::mat4x4(1.f), {size.x, size.y, 0.f});
        renderer2DData->textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData->squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData->squareVA);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D> texture)
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D> texture)
    {
        TEMPEST_PROFILE_FUNCTION();
        renderer2DData->textureShader->setVec4("uColour", glm::vec4(1.f));
        texture->bind();

        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), position) * glm::scale(glm::mat4x4(1.f), { size.x, size.y, 0.f });
        renderer2DData->textureShader->setMatrix4("uModelMatrix", transform);

        renderer2DData->squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData->squareVA);
        texture->unbind();
    }
}
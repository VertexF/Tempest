#include "PreComp.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Tempest/Platform/OpenGL/OpenGLShader.h"
#include "Tempest/Renderer/RendererCommands.h"

namespace Tempest 
{
    struct Renderer2DData 
    {
        ref<VertexArray> squareVA;
        ref<Shader> squareShader;
    };

    static Renderer2DData* renderer2DData;

    void Renderer2D::init() 
    {
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

        renderer2DData->squareShader = Shader::create("Assets/Shaders/FlatColour.glsl");
    }

    void Renderer2D::shutdown() 
    {
        delete renderer2DData;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        std::dynamic_pointer_cast<OpenGLShader>(renderer2DData->squareShader)->bind();
        std::dynamic_pointer_cast<OpenGLShader>(renderer2DData->squareShader)->setMatrix4Uniform("uViewProjectmatrix", camera.getViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(renderer2DData->squareShader)->setMatrix4Uniform("uModelMatrix", glm::mat4x4(1.f));
        //uModelMatrix
    }

    void Renderer2D::endScene() 
    {
    }

    //Primitive
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        drawQuad(glm::vec3(position.x, position.y, 0.f), size, colour);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour) 
    {
        std::dynamic_pointer_cast<OpenGLShader>(renderer2DData->squareShader)->bind();
        std::dynamic_pointer_cast<Tempest::OpenGLShader>(renderer2DData->squareShader)->setVec4Uniform("uColour", colour);

        renderer2DData->squareVA->bind();
        RendererCommands::drawIndexed(renderer2DData->squareVA);
    }
}
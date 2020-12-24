#ifndef RENDERER_2D_HDR
#define RENDERER_2D_HDR

#include "Tempest/Renderer/OrthographicCamera.h"
#include "Tempest/Renderer/Texture.h"

namespace Tempest 
{
    class Renderer2D 
    {
    public:
        //System
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        //Primitive
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour);

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& colour);
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& colour);

        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
    };
}

#endif //!RENDER_2D_HDR
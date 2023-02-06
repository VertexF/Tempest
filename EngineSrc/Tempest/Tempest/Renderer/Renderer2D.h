#ifndef RENDERER_2D_HDR
#define RENDERER_2D_HDR

#include "Tempest/Renderer/OrthographicCamera.h"
#include "Tempest/Renderer/Texture.h"
#include "Tempest/Renderer/SubTexture2D.h"

#include "stb_truetype.h"

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
        static void flush();

        //Primitive
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour);

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<SubTexture2D> subTexture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<SubTexture2D> subTexture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& colour);
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& colour);

        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const ref<SubTexture2D> subTexture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const ref<SubTexture2D> subTexture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawRotatedQuad(const glm::mat4& transform, const glm::vec2& size, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        static void drawText(const glm::vec2& position, const glm::vec2& size, const stbtt_aligned_quad& texCoords, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));
        static void drawText(const glm::vec3& position, const glm::vec2& size, const stbtt_aligned_quad& texCoords, const ref<Texture2D> texture, float tileFactor = 1.f, const glm::vec4& tint = glm::vec4(1.f));

        struct Statistics
        {
            uint32_t drawCalls = 0;
            uint32_t quadCount = 0;

            uint32_t getTotalVertices() const { return quadCount * 4; }
            uint32_t getTotalIndices() const { return quadCount * 6; }
        };
        static Statistics getStats();
        static void resetStats();
    private:
        static void flushAndReset();
    };
}

#endif //!RENDER_2D_HDR
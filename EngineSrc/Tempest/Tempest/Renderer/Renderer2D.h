#ifndef RENDERER_2D_HDR
#define RENDERER_2D_HDR

#include "Tempest/Renderer/OrthographicCamera.h"

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
    };
}

#endif //!RENDER_2D_HDR
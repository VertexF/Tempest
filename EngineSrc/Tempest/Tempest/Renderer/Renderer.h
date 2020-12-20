#ifndef RENDERER_HDR
#define RENDERER_HDR

#include "RendererCommands.h"
#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"

#include "Tempest/Core/Core.h"
#include <stdint.h>

namespace Tempest 
{
    class Renderer 
    {
    public:
        static void init();
        static void onResizeEvent(uint32_t width, uint32_t height);

        static void beginScene(OrthographicCamera &camera);
        static void endScene();

        static void submit(const ref<VertexArray> &vertexArray, const ref<Shader>& shader, const glm::mat4x4& transform = glm::mat4x4(1.f));

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    private:
        struct SceneData
        {
            glm::mat4x4 _viewProjectMatrix;
        };

        static SceneData* _sceneData;
    };
}

#endif // !RENDERER_HDR

#ifndef RENDERER_HDR
#define RENDERER_HDR

namespace Tempest 
{
    enum class RendererAPI 
    {
        NONE = 0,
        OPENGL = 1
    };

    class Renderer 
    {
    public:
        inline static RendererAPI getAPI() { return _rendererID; }
    private:
        static RendererAPI _rendererID;
    };
}

#endif // !RENDERER_HDR

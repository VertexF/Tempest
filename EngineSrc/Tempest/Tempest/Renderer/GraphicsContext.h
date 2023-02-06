#ifndef GRAPHICS_CONTEXT_HDR
#define GRAPHICS_CONTEXT_HDR

namespace Tempest 
{
    class GraphicsContext 
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
}

#endif // !GRAPHICS_CONTEXT_HDR

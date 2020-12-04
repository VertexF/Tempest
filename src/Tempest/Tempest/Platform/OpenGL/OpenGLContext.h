#ifndef OPENGL_CONTEXT_HDR
#define OPENGL_CONTEXT_HDR

#include "../Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Tempest 
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandler);

        virtual void init() override;
        virtual void swapBuffers() override;
    private:
        GLFWwindow *_windowHandle;
    };
}

#endif // !OPENGL_CONTEXT_HDR

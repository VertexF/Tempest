#include "PreComp.h"
#include "OpenGLContext.h"

#define GLEW_STATIC 1
#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace Tempest 
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandler) :
        _windowHandle(windowHandler)
    {
    }

    void OpenGLContext::init() 
    {
        glfwMakeContextCurrent(_windowHandle);
        //Here we are starting up glew.
        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        if (GLEW_OK != error)
        {
            TEMPEST_ERROR("GLEW could not start! {0}", glewGetErrorString(error));
        }
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(_windowHandle);
    }
}
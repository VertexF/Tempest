#include "PreComp.h"
#include "OpenGLContext.h"
#include "Tempest/Core/Core.h"

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
        TEMPEST_PROFILE_FUNCTION();

        glfwMakeContextCurrent(_windowHandle);
        //Here we are starting up glew.
        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        TEMPEST_CORE_ASSERT(GLEW_OK == error, "GLEW could not start! {0}", glewGetErrorString(error));

        TEMPEST_INFO("OpenGL Renderer: {0}, {1}", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
        TEMPEST_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::swapBuffers()
    {
        TEMPEST_PROFILE_FUNCTION();

        glfwSwapBuffers(_windowHandle);
    }
}
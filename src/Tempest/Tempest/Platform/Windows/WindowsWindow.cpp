#include "WindowsWindow.h"

#include "PreComp.h"

#include "../../Events/ApplicationEvents.h"
#include "../../Events/KeyEvents.h"
#include "../../Events/MouseEvents.h"
#include "../../Events/Event.h"

#include "../../Renderer/OpenGLContext.h"

namespace
{
    //Makes sure the intialisation of GLFW happens only once.
    bool GLFWIntialised = false;

    void GLFWErrorCallBack(int error, const char *errorString) 
    {
        TEMPEST_ERROR("GLFW Error ({0}): {1}", error, errorString);
    }
}

namespace Tempest
{
    //Here we are constructing a window with the default properties.
    Window* Window::create(const WindowProps& props) 
    { 
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) : _window(nullptr)
    {
        init(props);
    }

    WindowsWindow::~WindowsWindow() 
    {
        shutdown();
    }

    //The windows properties is just the basic properties this window need to 
    //be created.
    //Very important to note that the order of intailsation here:
    //1) You need to intialise GLFW 
    //2) You need to create the window GLFW 
    //3) You need to create an OpenGL context with GLFW
    //4) You need to intialise GLEW 
    void WindowsWindow::init(const WindowProps& props) 
    {
        _windowData.title = props.title;
        _windowData.width = props.width;
        _windowData.height = props.height;

        TEMPEST_INFO("Creating window: {0} [{1}, {2}]", _windowData.title, _windowData.width, _windowData.height);

        if (GLFWIntialised == false)
        {
            if (glfwInit() == false)
            {
                TEMPEST_ERROR("GLFW could not start!");
            }

            //With this set up we now set up the errors to use our logger.
            glfwSetErrorCallback(GLFWErrorCallBack);

            GLFWIntialised = true;
        }

        _window = glfwCreateWindow(static_cast<int>(_windowData.width), static_cast<int>(_windowData.height),
            _windowData.title.c_str(), nullptr, nullptr);

        _context = new OpenGLContext(_window);
        _context->init();

        glfwSetWindowUserPointer(_window, &_windowData);
        setVSync(true);

        //All these function are using predicates to use our custom event handlers. 
        glfwSetWindowSizeCallback(_window, [](GLFWwindow *wind, int width, int height) 
            {
                WindowData &windowData = *(static_cast<WindowData *>(glfwGetWindowUserPointer(wind)));
                windowData.width = width;
                windowData.height = height;

                WindowResizeEvent windowResizeEvent(width, height);
                windowData.eventCallback(windowResizeEvent);
            });

        glfwSetWindowCloseCallback(_window, [](GLFWwindow * wind) 
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));
                WindowClosedEvent closeEvent;

                windowData.eventCallback(closeEvent);
            });

        glfwSetKeyCallback(_window, [](GLFWwindow* wind, int key, int scanCode, int action, int mods)
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    PressedKeyEvent pressEvent(key, 0);
                    windowData.eventCallback(pressEvent);
                }
                break;
                case GLFW_RELEASE:
                {
                    PressedKeyEvent releaseEvent(key, 1);
                    windowData.eventCallback(releaseEvent);
                }
                break;
                case GLFW_REPEAT:
                {
                    PressedKeyEvent repeatEvent(key, 1);
                    windowData.eventCallback(repeatEvent);
                }
                break;
                }
            });

        glfwSetCharCallback(_window, [](GLFWwindow* wind, unsigned int character) 
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));

                TypedKeyEvent typedEvent(character);
                windowData.eventCallback(typedEvent);
            });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow *wind, int button, int action, int mods)
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));

                switch (action) 
                {
                case GLFW_PRESS:
                {
                    MouseButtonEventPressed pressEvent(button);
                    windowData.eventCallback(pressEvent);
                }
                break;
                case GLFW_RELEASE:
                {
                    MouseButtonEventReleased releaseEvent(button);
                    windowData.eventCallback(releaseEvent);
                }
                break;
                }
            });

        glfwSetScrollCallback(_window, [](GLFWwindow *wind, double x, double y) 
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));

                MouseScrolledEvent scrollEvent(static_cast<float>(x), static_cast<float>(y));
                windowData.eventCallback(scrollEvent);
            });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* wind, double x, double y) 
            {
                WindowData& windowData = *(static_cast<WindowData*>(glfwGetWindowUserPointer(wind)));

                MouseMovedEvent mouseMoved(static_cast<float>(x), static_cast<float>(y));
                windowData.eventCallback(mouseMoved);
            });
    }

    void WindowsWindow::shutdown() 
    {
        glfwDestroyWindow(_window);
    }

    //Currently just swaps the back buffer.
    void WindowsWindow::onUpdate() 
    {
        glfwPollEvents();
        _context->swapBuffers();
    }

    void WindowsWindow::setVSync(bool vsync) 
    {
        if (vsync) 
        {
            glfwSwapInterval(1);
        }
        else 
        {
            glfwSwapInterval(0);
        }

        _windowData.vSync = true;
    }

    bool WindowsWindow::isVSync() const 
    { 
        return _windowData.vSync;
    }
}
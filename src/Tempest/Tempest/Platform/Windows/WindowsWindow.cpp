#include "WindowsWindow.h"

#include "PreComp.h"

#include "../../Events/ApplicationEvents.h"
#include "../../Events/KeyEvents.h"
#include "../../Events/MouseEvents.h"
#include "../../Events/Event.h"

namespace
{
    bool GLFWIntialised = false;

    void GLFWErrorCallBack(int error, const char *errorString) 
    {
        TEMPEST_ERROR("GLFW Error ({0}): {1}", error, errorString);
    }
}

namespace Tempest
{
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

            glfwSetErrorCallback(GLFWErrorCallBack);

            GLFWIntialised = true;
        }

        _window = glfwCreateWindow(static_cast<int>(_windowData.width), static_cast<int>(_windowData.height), 
                                   _windowData.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, &_windowData);
        setVSync(true);

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

    void WindowsWindow::onUpdate() 
    {
        glfwPollEvents();
        glfwSwapBuffers(_window);
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
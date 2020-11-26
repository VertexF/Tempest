#include "WindowsWindow.h"

#include "PreComp.h"

namespace
{
    bool GLFWIntialised = false;
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
        if (::GLFWIntialised == false)
        {
            if (glfwInit() == false)
            {
                TEMPEST_ERROR("GLFW could not start!");
            }

            ::GLFWIntialised = true;
        }

        _window = glfwCreateWindow(static_cast<int>(_windowData.width), static_cast<int>(_windowData.height), 
                                   _windowData.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, &_windowData);
        setVSync(true);
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
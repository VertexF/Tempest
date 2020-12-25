#include "WindowsWindow.h"

#include "PreComp.h"

#include "Tempest/Events/ApplicationEvents.h"
#include "Tempest/Events/KeyEvents.h"
#include "Tempest/Events/MouseEvents.h"
#include "Tempest/Events/Event.h"

#include "Tempest/Platform/OpenGL/OpenGLContext.h"
#include "Tempest/Core/Core.h"
#include <backends/imgui_impl_glfw.h>

#include <stb_image.h>

namespace
{
    //Makes sure the intialisation of GLFW happens only once.
    bool GLFWIntialised = false;

    void GLFWErrorCallBack(int error, const char *errorString) 
    {
        TEMPEST_ERROR("GLFW Error ({0}): {1}", error, errorString);
    }
}

//TODO: Fix IMGUI mouse positioning and mouse buttons.
namespace Tempest
{
    //Here we are constructing a window with the default properties.
    scope<Window> Window::create(const WindowProps& props)
    { 
        return std::make_unique<WindowsWindow>(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) : _window(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();
        init(props);
    }

    WindowsWindow::~WindowsWindow() 
    {
        TEMPEST_PROFILE_FUNCTION();
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
        TEMPEST_PROFILE_FUNCTION();
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

        int width = 0;
        int height = 0;
        int channels;

        stbi_uc* imageData;
        {
            TEMPEST_PROFILE_SCOPE("WindowsWindow::init loading icon - stbi_load");
            imageData = stbi_load("Assets/Textures/Ship.png", &width, &height, &channels, 0);
        }

        GLFWimage icon = { width, height, imageData};

        glfwSetWindowIcon(_window, 1, &icon);

        glfwSetWindowUserPointer(_window, &_windowData);
        setVSync(true);

        //All these function are using predicates to use our custom event handlers. 
        glfwSetWindowSizeCallback(_window, [](GLFWwindow *wind, int width, int height) 
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));
                windowData.width = width;
                windowData.height = height;

                WindowResizeEvent windowResizeEvent(width, height);
                windowData.eventCallback(windowResizeEvent);
            });

        glfwSetWindowCloseCallback(_window, [](GLFWwindow * wind) 
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));
                WindowClosedEvent closeEvent;

                windowData.eventCallback(closeEvent);
            });

        glfwSetKeyCallback(_window, [](GLFWwindow* wind, int key, int scanCode, int action, int mods)
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));

                ImGuiIO& io = ImGui::GetIO();

                // Modifiers are not reliable across systems
                io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
                io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
                io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];

                switch (action)
                {
                case GLFW_PRESS:
                {
                    io.KeysDown[key] = true;
                    PressedKeyEvent pressEvent(key, 0);
                    windowData.eventCallback(pressEvent);
                    break;
                }
                case GLFW_RELEASE:
                {
                    io.KeysDown[key] = false;
                    ReleasedKeyEvent releaseEvent(key);
                    windowData.eventCallback(releaseEvent);
                    break;
                }
                case GLFW_REPEAT:
                {
                    PressedKeyEvent repeatEvent(key, 1);
                    windowData.eventCallback(repeatEvent);
                    break;
                }
                }
            });

        glfwSetCharCallback(_window, [](GLFWwindow* wind, unsigned int character) 
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));

                ImGuiIO& io = ImGui::GetIO();
                io.AddInputCharacter(character);

                TypedKeyEvent typedEvent(character);
                windowData.eventCallback(typedEvent);
            });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow *wind, int button, int action, int mods)
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));

                //if (action == GLFW_PRESS && button >= 0 && button < IM_ARRAYSIZE(g_MouseJustPressed))
                //    g_MouseJustPressed[button] = true;

                switch (action) 
                {
                case GLFW_PRESS:
                {
                    MouseButtonEventPressed pressEvent(button);
                    windowData.eventCallback(pressEvent);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonEventReleased releaseEvent(button);
                    windowData.eventCallback(releaseEvent);
                    break;
                }
                }
            });

        glfwSetScrollCallback(_window, [](GLFWwindow *wind, double x, double y) 
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));

                ImGuiIO& io = ImGui::GetIO();
                io.MouseWheelH += static_cast<float>(x);
                io.MouseWheel += static_cast<float>(y);

                MouseScrolledEvent scrollEvent(static_cast<float>(x), static_cast<float>(y));
                windowData.eventCallback(scrollEvent);
            });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* wind, double x, double y) 
            {
                WindowData& windowData = *(WindowData*)(glfwGetWindowUserPointer(wind));

                MouseMovedEvent mouseMoved(static_cast<float>(x), static_cast<float>(y));
                windowData.eventCallback(mouseMoved);
            });
    }

    void WindowsWindow::shutdown() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glfwDestroyWindow(_window);
    }

    //Currently just swaps the back buffer.
    void WindowsWindow::onUpdate() 
    {
        TEMPEST_PROFILE_FUNCTION();
        glfwPollEvents();
        _context->swapBuffers();
    }

    void WindowsWindow::setVSync(bool vsync) 
    {
        TEMPEST_PROFILE_FUNCTION();
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
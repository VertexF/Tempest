#include "WindowsInput.h"

#include <glfw/glfw3.h>

#include "../../Application.h"

namespace Tempest
{
    Input *Input::_input = new WindowsInput();

    bool WindowsInput::isKeyPressedImpl(int keyCode)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double xPos, yPos = 0.0;
        glfwGetCursorPos(window, &xPos, &yPos);

        return std::pair<float, float>(xPos, yPos);
    }

    float WindowsInput::getMouseXImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return x;
    }

    float WindowsInput::getMouseYImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return x;

        return y;
    }
}
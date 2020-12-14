#include "WindowsInput.h"

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

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

    glm::vec2 WindowsInput::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double xPos, yPos = 0.0;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float WindowsInput::getMouseXImpl()
    {
        return getMousePositionImpl().x;
    }

    float WindowsInput::getMouseYImpl()
    {
        return getMousePositionImpl().y;
    }
}
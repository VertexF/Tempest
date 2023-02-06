#include "Tempest/Core/Input.h"

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Tempest/Core/Application.h"

namespace Tempest
{
    bool Input::isKeyPressed(int keyCode)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keyCode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double xPos, yPos = 0.0;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float Input::getMouseX()
    {
        return getMousePosition().x;
    }

    float Input::getMouseY()
    {
        return getMousePosition().y;
    }

    float Input::getWorldCoordMouseX()
    {
        float screenWidth = static_cast<float>(Application::get().getWindow().getWidth());
        float screenHeight = static_cast<float>(Application::get().getWindow().getHeight());
        float halfScreenWidth = screenWidth / 2.f;

        float incorrectScaleButCorrectCoord = (halfScreenWidth - getMousePosition().x);
        float theOneScale = incorrectScaleButCorrectCoord / halfScreenWidth;
        float result = theOneScale * ((screenWidth / screenHeight) * -Application::get().getCurrentLayerZoomLevel());

        return result;
    }

    float Input::getWorldCoordMouseY() 
    {
        float halfScreenHeight = static_cast<float>(Application::get().getWindow().getHeight()) / 2.f;

        float incorrectScaleButCorrectCoord = (halfScreenHeight - getMousePosition().y);
        float theOneScale = incorrectScaleButCorrectCoord / halfScreenHeight;
        float result = theOneScale * Application::get().getCurrentLayerZoomLevel();

        return result;
    }
}
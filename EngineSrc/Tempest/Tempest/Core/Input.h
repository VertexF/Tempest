#ifndef INPUT_HDR
#define INPUT_HDR

#include "PreComp.h"

#include <glm/glm.hpp>

namespace Tempest 
{
    class Input
    {
    public:
        static bool isKeyPressed(int keyCode);
        static bool isMouseButtonPressed(int button);
        static glm::vec2 getMousePosition();
        static float getMouseX();
        static float getMouseY();

        static float getWorldCoordMouseX();
        static float getWorldCoordMouseY();
    };
}

#endif // !INPUT_HDR

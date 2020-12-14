#ifndef INPUT_HDR
#define INPUT_HDR

#include "PreComp.h"

#include <glm/glm.hpp>

namespace Tempest 
{
    class Input
    {
    public:
        inline static bool isKeyPressed(int keyCode) { return _input->isKeyPressedImpl(keyCode); }
        inline static bool isMouseButtonPressed(int button) { return _input->isMouseButtonPressedImpl(button); }
        inline static glm::vec2 getMousePosition() { return _input->getMousePositionImpl();  }
        inline static float getMouseX() { return _input->getMouseXImpl(); }
        inline static float getMouseY() { return _input->getMouseYImpl(); }
    private:
        virtual bool isKeyPressedImpl(int keyCode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual glm::vec2 getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;
    private:
        static Input* _input;
    };
}

#endif // !INPUT_HDR

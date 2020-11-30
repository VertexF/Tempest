#ifndef INPUT_HDR
#define INPUT_HDR

#include "PreComp.h"

namespace Tempest 
{
    class TEMPEST_EXPORT Input
    {
    public:
        inline static bool isKeyPressed(int keyCode) { return _input->isKeyPressedImpl(keyCode); }
        inline static bool isMouseButtonPressed(int button) { return _input->isMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> getMousePosition() { return _input->getMousePositionImpl();  }
        inline static float getMouseX() { return _input->getMouseXImpl(); }
        inline static float getMouseY() { return _input->getMouseYImpl(); }
    private:
        virtual bool isKeyPressedImpl(int keyCode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;
    private:
        static Input* _input;
    };
}

#endif // !INPUT_HDR

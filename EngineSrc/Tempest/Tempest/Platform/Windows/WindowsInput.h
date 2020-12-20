#ifndef WINDOWS_INPUT_HDR
#define WINDOWS_INPUT_HDR

#include "Tempest/Core/Input.h"
#include <glm/glm.hpp>

namespace Tempest 
{
    class WindowsInput : public Input 
    {
    protected:
        virtual bool isKeyPressedImpl(int keyCode) override;
        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual glm::vec2 getMousePositionImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };
}

#endif // !WINDOWS_INPUT_HDR

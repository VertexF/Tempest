#ifndef WINDOWS_INPUT_HDR
#define WINDOWS_INPUT_HDR

#include "../../Input.h"
namespace Tempest 
{
    class WindowsInput : public Input 
    {
    protected:
        virtual bool isKeyPressedImpl(int keyCode) override;
        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> getMousePositionImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };
}

#endif // !WINDOWS_INPUT_HDR

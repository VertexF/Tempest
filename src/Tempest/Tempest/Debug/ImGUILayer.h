#ifndef IMGUI_LAYER
#define IMGUI_LAYER

#include "PreComp.h"

#include "../Layer.h"
#include "../Events/Event.h"
#include "../Events/MouseEvents.h"
#include "../Events/KeyEvents.h"
#include "../Events/ApplicationEvents.h"

namespace Tempest 
{
    class TEMPEST_EXPORT ImGuiLayer : public Layer 
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onEvent(Event& e);
        void onUpdate();
        void onAttach();
        void onDetach();
    private:
        bool onMouseButtonPressedEvent(MouseButtonEventPressed &pressEvent);
        bool onMouseButtonReleaseEvent(MouseButtonEventReleased& releaseEvent);
        bool onMouseMovedEvent(MouseMovedEvent& mouseMoved);
        bool onMouseScrollEvent(MouseScrolledEvent& mouseScrolled);

        bool onKeyPressedEvent(PressedKeyEvent& keyPressed);
        bool onKeyReleasedEvent(ReleasedKeyEvent& keyReleased);
        bool onKeyTypedEvent(TypedKeyEvent& keyTyped);
        bool onWindowResizeEvent(WindowResizeEvent& windowResized);

    private:
        float _time = 0.f;
    };
}

#endif // !IMGUI_LAYER

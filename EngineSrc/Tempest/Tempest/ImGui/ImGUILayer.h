#ifndef IMGUI_LAYER
#define IMGUI_LAYER

#include "PreComp.h"

#include "Tempest/Core/Layer.h"
#include "Tempest/Events/Event.h"
#include "Tempest/Events/MouseEvents.h"
#include "Tempest/Events/KeyEvents.h"
#include "Tempest/Events/ApplicationEvents.h"

namespace Tempest 
{
    class ImGuiLayer : public Layer 
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onImGuiRender() override;
        virtual void onEvent(Event& e) override;

        void begin();
        void end();

        void blockEvents(bool block) { _blockEvents = block; }

        void setDarkThemeColors();
    private:
        float _time = 0.f;
        bool _blockEvents = true;
    };
}

#endif // !IMGUI_LAYER

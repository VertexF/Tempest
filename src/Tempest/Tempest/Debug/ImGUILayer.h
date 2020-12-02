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

        //void onImGuiRender();
        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onImGuiRender() override;

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

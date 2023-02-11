#ifndef MENU_LAYER_HDR
#define MENU_LAYER_HDR

#include <Tempest.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"

namespace game
{
    class MenuLayer : public Tempest::Layer
    {
    public:
        MenuLayer();
        virtual ~MenuLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(Tempest::TimeStep timeStep) override;
        virtual void onEvent(Tempest::Event& e) override;
        virtual void onImGuiRender() override;
        virtual bool isFinished() const override;
    private:
        bool onKeyPressed(Tempest::PressedKeyEvent& e);
        bool onKeyReleased(Tempest::ReleasedKeyEvent& e);
    private:
        Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;

        Tempest::scope<Tempest::TextRenderer> _titleText;
        Tempest::scope<Tempest::TextRenderer> _spaceText;

        float _posX;
        float _posY;

        bool finished = false;
    };
}

#endif // !MENU_LAYER_HDR

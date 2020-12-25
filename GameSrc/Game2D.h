#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/MouseEvents.h"

#include "Level.h"

class Game2D : public Tempest::Layer
{
public:
    Game2D();
    virtual ~Game2D() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Tempest::TimeStep timeStep) override;
    virtual void onEvent(Tempest::Event& e) override;

    virtual void onImGuiRender() override;
private:
    bool onMouseButtonPressed(Tempest::MouseButtonEventPressed& e);
private:
    Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;

    Level _level;
    ImFont* _font;

    float _time = 0.f;
    bool _blink = false;

    enum class GameState
    {
        PLAY = 0,
        MAIN_MENU,
        GAME_OVER,
        START
    };

    GameState _gameState = GameState::START;
};

#endif //!GAME_2D_HDR
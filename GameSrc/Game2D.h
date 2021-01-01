#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"

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
    glm::vec4 _squareColour;

    Tempest::ref<Tempest::Texture2D> _backgroundTexture;
    Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;

    Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;
    std::vector<float> _xPos;
    std::vector<float> _yPos;
};


#endif //!GAME_2D_HDR
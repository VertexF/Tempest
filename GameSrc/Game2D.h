#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>

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
    Tempest::ref<Tempest::Shader> _squareShader;
    Tempest::ref<Tempest::VertexArray> _squareVA;
    glm::vec4 _squareColour;

    Tempest::ref<Tempest::Texture2D> _backgroundTexture;
    Tempest::ref<Tempest::Texture2D> _dirt;
    Tempest::ref<Tempest::Texture2D> _water;
    Tempest::ref<Tempest::Texture2D> _grass;

    Tempest::OrthographicalCameraController _cameraController;

    int _levelWidth;
    int _levelHeight;
    std::wstring _levelMap;
};

#endif //!GAME_2D_HDR
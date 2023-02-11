#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>
#include <ImGui.h>
#include <memory>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"


namespace game
{
    class Player;

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

        virtual bool isFinished() const override { return false; }
    private:
        bool onKeyPressed(Tempest::PressedKeyEvent& e);
        bool onKeyReleased(Tempest::ReleasedKeyEvent& e);
    private:
        Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;
        Tempest::scope<Tempest::TextRenderer> _scoreText;
        Tempest::scope<Tempest::TextRenderer> _levelText;
        Tempest::scope<Tempest::TextRenderer> _gameOverText;

        glm::vec4 _squareColour;
        Tempest::ref<Tempest::Texture2D> _backgroundTexture;

        uint32_t _spellSoundBuffer = 0;
        uint32_t _magicFailSoundBuffer = 0;

        Tempest::ref<Tempest::SoundDevice> _soundDevice;
        Tempest::ref<Tempest::SoundBuffer> _soundBuffer;
        Tempest::ref<Tempest::SoundSource> _mySource;

        bool _hasWon = false;
        bool _isDead = false;

        int _score = 0;
        uint32_t _playerLives = 0;
        float _totalTime = 0.f;

        std::vector<float> _xPos;
        std::vector<float> _yPos;
    };
}

#endif //!GAME_2D_HDR
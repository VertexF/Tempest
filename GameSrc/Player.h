#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <Tempest.h>

#include "Colour.h"
#include "Player.h"
#include "ParticalSystem.h"

class Player 
{
public:
    Player();

    void loadAssets();
    void onUpdate(Tempest::TimeStep ts);
    void onRender();

    void onImGuiRender();
    void reset();

    float getRotation() { return (_velocity.y * 4.f - 90.f); }
    const glm::vec2& getPosition() const { return _position; }

    uint32_t getScore() const { return static_cast<uint32_t>((_position.x + 10.f) / 10.f);  }
private:
    glm::vec2 _position = { -10.f, 4.f };
    glm::vec2 _velocity = { 5.f, 0.f };

    float _enginePower = 0.8f;
    float _gravity = 0.6f;

    float _time = 0.f;
    float _smokeInterval = 0.4f;
    float _smokeEmitTime = _smokeInterval;

    ParticalProps _smokeParticalProps, _fireParticalProps;
    ParticalSystem _particalSystem;

    Tempest::ref<Tempest::Texture2D> _shipTexture;
};

#endif // !PLAYER_HDR

#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <Tempest.h>

#include "Player.h"

class Player 
{
public:
    Player();

    void loadAssets();
    void onUpdate(Tempest::TimeStep ts);
    void onRender();

    void onImGuiRender();
    void reset();

    float getRotation() { return _rotation; }
    const glm::vec2& getPosition() const { return _position; }
private:
    glm::vec2 _position = { 0.f, 0.f };
    glm::vec2 _velocity = { 0.f, 0.f };

    float _rotation = 0.f;
};

#endif // !PLAYER_HDR

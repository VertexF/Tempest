#ifndef LEVEL_HDR
#define LEVEL_HDR

#include "Player.h"

struct Pillar 
{
    glm::vec3 topPosition = { 0.f, 10.f, 0.f };
    glm::vec3 bottomPosition = { 10.f, 10.f, 0.f };

    glm::vec2 topScale = { 15.f, 20.f };
    glm::vec2 bottomScale = { 15.f, 20.f  };
};

class Level 
{
public:
    void init();
    void onUpdate(Tempest::TimeStep ts);
    void onRender();

    void onImGuiRender();

    bool isGameOver() const { return _gameOver; }
    void reset();

    Player& getPlayer() { return _player; }
private:
    void createPillar(int index, float offset);
    bool collisionTest();

    void gameOver();
private:
    Player _player;

    bool _gameOver = false;

    float _pillarTarget = 30.f;
    int _pillarIndex = 0;
    glm::vec3 _pillarHSV = { 0.f, 0.8f, 0.8f };

    std::vector<Pillar> _pillars;

    Tempest::ref<Tempest::Texture2D> _triangleTexture;
};

#endif // !LEVEL_HDR

#include <iostream>
#include <Tempest.h>

class Game : public Tempest::Application
{
public:
    Game() {}
    ~Game() {}
};

Tempest::Application* Tempest::createApplication() 
{
    return new Game();
}
#include <iostream>
#include <Tempest.h>

class Game : public Tempest::Application
{
public:
    Game() {}
    ~Game() {}
};

int main(int argc, char* argv[]) 
{
    Game* game = new Game();
    game->run();
    delete game;

    return 0;
}
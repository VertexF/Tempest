#include <iostream>
#include "Tempest/Application.h"

class Game : public Tempest::Application
{
    Game() {}
    ~Game() {}
};

int main() 
{
    Tempest::Application *tempest = new Tempest::Application();
    tempest->run();
    delete tempest;

    return 0;
}
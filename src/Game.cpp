#include <iostream>
#include <Tempest.h>

class ExampleLayer : public Tempest::Layer 
{
public:
    ExampleLayer() : Layer("Example Layer")
    {
    }

    void onUpdate() override 
    {
        //TEMPEST_INFO("ExampleLayer::Update");
    }

    void onEvent(Tempest::Event &e) override
    {
        //TEMPEST_TRACE("Game Event :{0} ", e);
    }
};

class Game : public Tempest::Application
{
public:
    Game() 
    {
        pushLayer(new ExampleLayer());
    }

    ~Game() {}
};

Tempest::Application* Tempest::createApplication() 
{
    return new Game();
}
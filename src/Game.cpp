#include <iostream>
#include <Tempest.h>

//The client also create it own layers depending on what it needs.
class ExampleLayer : public Tempest::Layer 
{
public:
    ExampleLayer() : Layer("Example Layer")
    {
    }

    void onUpdate() override 
    {
        if (Tempest::Input::isKeyPressed(TEMP_KEY_TAB)) 
        {
            TEMPEST_TRACE("Tab is pressed");
        }
    }

    void onEvent(Tempest::Event &e) override
    {
        
    }
};

//The client uses the application as a template to create the game.
class Game : public Tempest::Application
{
public:
    Game() 
    {
        pushLayer(new ExampleLayer());
        pushOverlay(new Tempest::ImGuiLayer());
    }

    ~Game() {}
};

//We kick start the engine by using our client class that is 
//inherited from the the engine.
Tempest::Application* Tempest::createApplication() 
{
    return new Game();
}
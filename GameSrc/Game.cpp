#include <iostream>
#include <Tempest.h>

#include "Tempest/Core/EntryPoint.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Tempest/Platform/OpenGL/OpenGLShader.h"
#include "Tempest/Renderer/Shader.h"

#include "Game2D.h"

//The client uses the application as a template to create the game.
class Game : public Tempest::Application
{
public:
    Game() 
    {
        pushLayer(new Game2D());
    }

    ~Game() {}
};

//We kick start the engine by using our client class that is 
//inherited from the the engine.
Tempest::Application* Tempest::createApplication() 
{
    return new Game();
}
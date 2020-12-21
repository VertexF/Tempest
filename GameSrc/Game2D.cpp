#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

Game2D::Game2D() : Layer("Game"), _cameraController(1280.f / 720.f), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f})
{
    _levelWidth = 64;
    _levelHeight = 16;
    _levelMap += L"###########################################################.....";
    _levelMap += L"#............................o.........oooooooooooo.......#.....";
    _levelMap += L"#.........???................oo.........ooooooooo#........#.....";
    _levelMap += L"#.........???.................oo...........oooo..####.....#.....";
    _levelMap += L"#...............................oo.......oooooo....###....#.....";
    _levelMap += L"#................................o......ooooo.............#.....";
    _levelMap += L"#...............####..............oo.ooooo................#.....";
    _levelMap += L"#.............#######..............oooo...................#.....";
    _levelMap += L"#...............###...............ooooo...................#.....";
    _levelMap += L"#...............................ooooo.....................#.....";
    _levelMap += L"#.............................oooooo......................#.....";
    _levelMap += L"#............................oooo........................##.....";
    _levelMap += L"#........................####oooo.......................###.....";
    _levelMap += L"#................##############.......................#####.....";
    _levelMap += L"#...........#########################........##############.....";
    _levelMap += L"###########################################################.....";
}

void Game2D::onAttach() 
{
    _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/background.png");
    _dirt = Tempest::Texture2D::create("Assets/Textures/rock.png");
    _water = Tempest::Texture2D::create("Assets/Textures/water.png");
    _grass = Tempest::Texture2D::create("Assets/Textures/grass.png");
}

void Game2D::onDetach() 
{
}

void Game2D::onUpdate(Tempest::TimeStep timeStep) 
{
    auto GetTile = [&](int x, int y)
    {
        if (x >= 0 && x < _levelWidth && y >= 0 && y < _levelHeight)
            return _levelMap[y * _levelWidth + x];
        else
            return L' ';
    };

    auto SetTile = [&](int x, int y, wchar_t c)
    {
        if (x >= 0 && x < _levelWidth && y >= 0 && y < _levelHeight)
            _levelMap[y * _levelWidth + x] = c;
    };

    _cameraController.onUpdate(timeStep);

    Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
    Tempest::RendererCommands::clear();

    Tempest::Renderer2D::beginScene(_cameraController.getCamera());

    for (int x = 0; x < 150; x++)
    {
        for (int y = 0; y < 150; y++)
        {
            wchar_t sTileID = GetTile(x, y);
            switch (sTileID)
            {
            case L'#': // Solid Block
                Tempest::Renderer2D::drawQuad({ x - 8.5, -y + 7.5 }, { 1.f, 1.f }, _dirt);
                break;
            case L'o': // Solid Block
                Tempest::Renderer2D::drawQuad({ x - 8.5, -y + 7.5 }, { 1.f, 1.f }, _water);
                break;
            case L'?': // Solid Block
                Tempest::Renderer2D::drawQuad({ x - 8.5, -y + 7.5 }, { 1.f, 1.f }, _grass);
                break;
            }
        }
    }

    //Tempest::Renderer2D::drawQuad({ 0.f, 0.f }, {1.f, 1.f}, _squareColour);
    //Tempest::Renderer2D::drawQuad({ 3.f, -1.f }, { 0.5f, 2.f }, { 0.2f, 0.3f, 0.8f, 1.f });
    Tempest::Renderer2D::drawQuad({ 0.f, 0.f -0.1f }, { 100.f, 100.f }, _backgroundTexture);

    Tempest::Renderer2D::endScene();
}

void Game2D::onEvent(Tempest::Event& e)
{
    _cameraController.onEvent(e);
}

void Game2D::onImGuiRender() 
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

    ImGui::End();
}

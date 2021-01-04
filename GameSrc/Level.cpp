#include "PreComp.h"
#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
    const uint32_t MAP_WIDTH = 30;
    const char* MAP =
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
        "WWWWWWWDDDDDDDDDDDWWWWWWWWWWWW"
        "WWWWWWDDDDDDDDDDDDDDDWWWWWWWWW"
        "WWWDDDDDDDDDDDDDDDDDDWWWWWWWWW"
        "WWWDDDDDWWDDDDDDDDDDDWWWWWWWWW"
        "WWWWDDDWWWWDDDDDDDDDDWWWWWWWWW"
        "WWWWDDDWWWWDDDDDDDDDWWWWWWWWWW"
        "WWDDDDDDDDDDDDDDDDDDDWWWWWWWWW"
        "WWWWDDDDDDDDDDDDDDDWWWWWWWWWWW"
        "WWWWDDDDDDDDDDDDDDDDWWWWWWWWWW"
        "WWWDDDDDDDDDDDDDDDDDWWWWWWWWWW"
        "WWWWDDDDDDDDDDDDDDDDDDDDDDDWWW"
        "WWWWWWWWDDDDDDDDDDDDDDDDDDDDWW"
        "WWWWWDDDDDDDDDDDDDDDDDDDDDDDWW"
        "WWWWWDDDDDDDDDDDDDDDDDDDDDDWWW"
        "WWWWDDDDDDDDDDDDDDDDDDDDDDDWWW"
        "WWWWWWDDDDDDDDDDDDDDDDDDDDDWWW"
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
}

void Level::init() 
{
    TEMPEST_PROFILE_FUNCTION();

    _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/RPGpack_sheet_2X.png");

    _bushTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 11 }, { 128, 128 });
    _treeTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 2, 1 }, { 128, 128 }, { 1, 2 });
    _textureMap['D'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 6, 11 }, { 128, 128 });
    _textureMap['W'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 11, 11 }, { 128, 128 });

    _mapWidth = MAP_WIDTH;
    _mapHeight = strlen(MAP) / MAP_WIDTH;
}

void Level::onUpdate(Tempest::TimeStep ts) 
{
    TEMPEST_PROFILE_FUNCTION();
    _player.onUpdate(ts);
}

void Level::onRender() 
{
    TEMPEST_PROFILE_FUNCTION();

    for (uint32_t y = 0; y < _mapHeight; ++y)
    {
        for (uint32_t x = 0; x < _mapWidth; ++x)
        {
            char tileType = MAP[x + y * _mapWidth];
            if (_textureMap.find(tileType) != _textureMap.end())
            {
                Tempest::Renderer2D::drawQuad({ x - _mapWidth / 2.f, _mapHeight - y - _mapHeight / 2.f, 0.5f }, { 1.f, 1.f }, _textureMap[tileType]);
            }
            else
            {
                Tempest::Renderer2D::drawQuad({ x - _mapWidth / 2.f, _mapHeight - y - _mapHeight / 2.f, -1.0f }, { 1.f, 1.f }, { 1.0, 0.0, 1.0, 1.0 });
            }
        }
    }

    Tempest::Renderer2D::drawQuad({ 0.f, 0.f, 0.0f }, { 1.f, 1.f }, _bushTexture);
    Tempest::Renderer2D::drawQuad({ 1.f, 0.5f, 0.0f }, { 1.f, 2.f }, _treeTexture);
}

void Level::onImGuiRender() 
{
    TEMPEST_PROFILE_FUNCTION();
    _player.onImGuiRender();
}

void Level::reset()
{
    TEMPEST_PROFILE_FUNCTION();
    _gameOver = false;

    _player.reset();
}
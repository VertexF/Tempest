#include "PreComp.h"
#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
    const uint32_t MAP_WIDTH = 30;
    const char* MAP =
        "###################GGGGggggggg"
        "##Gg##DDDdDDDDDDDDDDDDDDDgGGgg"
        "##g#DDDDDDDDDDDDDDDDDdDDDgGGGg"
        "###DDDDDDdDDDDDDDggDDDDdDDDDgg"
        "##DDDDDDDDDDDDDDg#ggDDDDdDDDDg"
        "#DDDDdDDDDdDDDDDg#gDDDDDDDDDDg"
        "#GGDDDDDDDDDDDDDDgDDDDdDDDDDDg"
        "#gGGgDdDDDDDdDDDDDDDdDDDDDDDDg"
        "#gGGGgDDdDDdDDDDDdDDDDDDDDDDgg"
        "#gGGGGGDDDDDDDDDdDDDDDDDDDDggg"
        "#gDDGGGGGgGgGGDDDDDDDDDDDDDggg"
        "#DDDDGDGggGGDDDDDDdDDDDDDDDggg"
        "#DDDDDGGGGGGGDDDDDDDDDDDDDgggg"
        "gDDDDDDDDDDDDDDDDDdDdDDDDgg###"
        "ggDDDDDDDddDDDddDdDDdDDDg#####"
        "ggggDDDDDDDddDDDDDDDDGGGGGGGGG"
        "g###ggDDDDDDDddDdDDDDDDDGGGGGG"
        "gg##gggggggggggggggggggggggGGG";
}

namespace game
{
    void Level::init()
    {
        TEMPEST_PROFILE_FUNCTION();

        _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/sprites.png");

        _textureMap['G'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 0, 0 }, { 127, 128 });
        _textureMap['g'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 0 }, { 127, 128 });
        _textureMap['#'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 2, 0 }, { 126, 128 });

        _textureMap['D'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 3, 0 }, { 127, 128 });
        _textureMap['d'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 4, 0 }, { 127, 128 });

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
}
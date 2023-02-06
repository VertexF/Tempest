#ifndef LEVEL_HDR
#define LEVEL_HDR

#include "Player.h"
#include "Tempest/Renderer/Texture.h"
#include "Tempest/Renderer/SubTexture2D.h"

namespace game
{
    class Level
    {
    public:
        void init();
        void onUpdate(Tempest::TimeStep ts);
        void onRender();

        void onImGuiRender();

        bool isGameOver() const { return _gameOver; }
        void reset();

        const Player& getPlayer() const { return _player; }
    private:
        Player _player;

        Tempest::ref<Tempest::Texture2D> _backgroundTexture;
        Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;
        Tempest::ref<Tempest::SubTexture2D> _bushTexture;
        Tempest::ref<Tempest::SubTexture2D> _treeTexture;

        uint32_t _mapWidth;
        uint32_t _mapHeight;

        std::unordered_map<char, Tempest::ref<Tempest::SubTexture2D>> _textureMap;

        bool _gameOver = false;
    };
}

#endif // !LEVEL_HDR

#ifndef RESOURCE_MANAGER_HDR
#define RESOURCE_MANAGER_HDR

#include "Tempest/Renderer/Texture.h"

namespace game
{
    class ResourceManager
    {
    public:
        enum class SPRITESHEET_TYPE 
        {
            SHIP,
            TOTAL
        };

        ResourceManager();

        Tempest::ref<Tempest::Texture2D> getSpriteSheet(SPRITESHEET_TYPE type);

    public:
        Tempest::ref<Tempest::Texture2D> _shipSpriteSheet;
    };
}
#endif // !RESOURCE_MANAGER_HDR

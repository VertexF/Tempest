#include "PreComp.h"
#include "ResourceManager.h"

#include "Tempest/Core/Log.h"
#include "Tempest/Debug/Instrumentor.h"

namespace game 
{
    ResourceManager::ResourceManager() 
    {
        TEMPEST_PROFILE_FUNCTION();
        _shipSpriteSheet = Tempest::Texture2D::create("Assets/Textures/ships.png");
    }

    Tempest::ref<Tempest::Texture2D> ResourceManager::getSpriteSheet(ResourceManager::SPRITESHEET_TYPE type)
    {
        TEMPEST_PROFILE_FUNCTION();
        switch (type) 
        {
        case SPRITESHEET_TYPE::SHIP:
            return _shipSpriteSheet;
        default:
            TEMPEST_CORE_ASSERT("Spritesheet you selected does not exist", true);
            return nullptr;
        }
    }
}
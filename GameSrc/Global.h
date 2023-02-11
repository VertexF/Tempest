#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "Singleton.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Tempest/Audio/Audio.h"

namespace game 
{
#define ENTITY_MANAGER (Singleton<EntityManager>::getInstance())
#define AUDIO_MANAGER (Singleton<Tempest::Audio>::getInstance())
#define RESOURCE_MANAGER (Singleton<ResourceManager>::getInstance())

    void createGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR

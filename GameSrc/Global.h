#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "Singleton.h"
#include "EntityManager.h"

namespace game 
{
#define ENTITY_MANAGER (Singleton<EntityManager>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR

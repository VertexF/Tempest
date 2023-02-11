#ifndef ENTITY_MANAGER_HDR
#define ENTITY_MANAGER_HDR

#include <map>
#include <memory>
#include <vector>

#include "BaseEntity.h"

namespace game 
{
    class EntityManager 
    {
    public:
        enum class EntityType : uint32_t
        {
            PLAYER = 0,
            ENEMY,
            ATTACKER,
            TOTAL_ENTITIES
        };
    public:
        EntityManager() = default;

        uint32_t instantiate(EntityType type);

        std::shared_ptr<BaseEntity> get(uint32_t id);
        std::shared_ptr<BaseEntity> getPlayer();

        std::vector<std::shared_ptr<BaseEntity>> getEnemies();
        std::vector<std::shared_ptr<BaseEntity>> getAllEntity();

        void remove(uint32_t id);

        bool isRemoved(uint32_t id);
        bool isPlayerRemoved();
        bool isPlayer(uint32_t id) const;

        size_t size() const;
        std::unordered_map<uint32_t, EntityType> getEntities();

    private:
        std::unordered_map<uint32_t, EntityType> _entities;
        std::vector<std::shared_ptr<BaseEntity>> _entityList;

        uint32_t _playerID = -1;
    };
}

#endif // !ENTITY_MANAGER_HDR

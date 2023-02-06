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

        int instantiate(EntityType type);

        std::shared_ptr<BaseEntity> get(int id);
        std::shared_ptr<BaseEntity> getPlayer();

        std::vector<std::shared_ptr<BaseEntity>> getEnemies();
        std::vector<std::shared_ptr<BaseEntity>> getAllEntity();

        void remove(int id);

        bool isRemoved(int id);
        bool isPlayerRemoved();
        bool isPlayer(int id) const;

        size_t size() const;
    private:
        std::unordered_map<int, EntityType> _entities;
        std::vector<std::shared_ptr<BaseEntity>> _entityList;

        int _playerID = -1;
    };
}

#endif // !ENTITY_MANAGER_HDR

#include "EntityManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Attacker.h"
#include <Tempest.h>

namespace game 
{
    uint32_t EntityManager::instantiate(EntityType type)
    {
        uint32_t ID = 99999;
        switch (type) 
        {
        case EntityType::PLAYER:
        {
            _playerID = static_cast<uint32_t>(_entities.size());
            std::shared_ptr<Player> player = std::make_shared<Player>(_playerID);
            _entities.insert({ _playerID, EntityType::PLAYER });
            _entityList.push_back(player);
            return _playerID;
            break;
        }
        case EntityType::ENEMY:
        {
            ID = static_cast<uint32_t>(_entities.size());
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(ID);
            _entities.insert({ ID, EntityType::ENEMY });
            _entityList.push_back(enemy);
            return ID;
            break;
        }
        case EntityType::ATTACKER:
        {
            ID = static_cast<uint32_t>(_entities.size());
            std::shared_ptr<Attacker> attacker = std::make_shared<Attacker>(ID);
            _entities.insert({ ID, EntityType::ATTACKER });
            _entityList.push_back(attacker);
            return ID;
            break;
        }
        default:
            TEMPEST_CORE_ASSERT("Entity type does not exists.", true);
            return ID;
        }
    }

    std::shared_ptr<BaseEntity> EntityManager::get(uint32_t id)
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
        {
            size_t index = std::distance(_entities.begin(), it);
            return std::shared_ptr<BaseEntity>(_entityList[index]);
        }

        //This should be removed when I have a more complete system because this isn't an error.
        //TEMPEST_ERROR("Debug only! This Entity with ID {0} does not exist.", id);
        return nullptr;
    }

    std::shared_ptr<BaseEntity> EntityManager::getPlayer()
    {
        auto it = _entities.find(_playerID);
        if (it != _entities.end())
        {
            return std::shared_ptr<BaseEntity>(_entityList[it->first]);
        }

        //This should be removed when I have a more complete system because this isn't an error.
        TEMPEST_ERROR("Debug only! This Entity with ID {0} does not exist.", _playerID);
        return nullptr;
    }

    std::vector<std::shared_ptr<BaseEntity>> EntityManager::getEnemies()
    {
        std::vector<std::shared_ptr<BaseEntity>> enemiesList;
        for (uint32_t i = 0; i < _entities.size(); i++)
        {
            auto it = _entities.find(i);
            if (it != _entities.end() && (it->second == EntityType::ENEMY || it->second == EntityType::ATTACKER))
            {
                enemiesList.push_back(_entityList[i]);
            }
        }

        return enemiesList;
    }

    std::vector<std::shared_ptr<BaseEntity>> EntityManager::getAllEntity()
    {
        return _entityList;
    }

    void EntityManager::remove(uint32_t id)
    {
        auto it = _entities.find(id);
        if (it == _entities.end())
        {
            TEMPEST_ERROR("This Entity with ID {0} does not exist.", id);
            return;
        }

        uint32_t toDeleteIndex = static_cast<uint32_t>(std::distance(_entities.begin(), it));
        EntityType entityType = it->second;

        std::swap(_entityList[toDeleteIndex], _entityList.back());
        _entityList.pop_back();

        _entities[toDeleteIndex] = entityType;
        _entities.erase(id);
    }

    bool EntityManager::isRemoved(uint32_t id)
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
        {
            return false;
        }
        return true;
    }

    bool EntityManager::isPlayerRemoved()
    {
        auto it = _entities.find(_playerID);
        if (it != _entities.end())
        {
            return false;
        }
        return true;
    }

    bool EntityManager::isPlayer(uint32_t id) const
    {
        return(_playerID == id);
    }

    size_t EntityManager::size() const
    {
        return _entityList.size();
    }

    std::unordered_map<uint32_t, EntityManager::EntityType> EntityManager::getEntities()
    {
        return _entities;
    }
}
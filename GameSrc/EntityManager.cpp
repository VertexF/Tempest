#include "EntityManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Attacker.h"
#include <Tempest.h>

namespace game 
{
    int EntityManager::instantiate(EntityType type)
    {
        int ID;
        switch (type) 
        {
        case EntityType::PLAYER:
        {
            _playerID = _entities.size();
            std::shared_ptr<Player> player = std::make_shared<Player>(_playerID);
            _entities.insert({ _playerID, EntityType::PLAYER });
            _entityList.push_back(player);
            return _playerID;
            break;
        }
        case EntityType::ENEMY:
        {
            ID = _entities.size();
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(ID);
            _entities.insert({ ID, EntityType::ENEMY });
            _entityList.push_back(enemy);
            return ID;
            break;
        }
        case EntityType::ATTACKER:
            ID = _entities.size();
            std::shared_ptr<Attacker> attacker = std::make_shared<Attacker>(ID);
            _entities.insert({ ID, EntityType::ATTACKER });
            _entityList.push_back(attacker);
            return ID;
            break;
        }
    }

    std::shared_ptr<BaseEntity> EntityManager::get(int id)
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
        {
            return std::shared_ptr<BaseEntity>(_entityList[it->first]);
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
        for (size_t i = 0; i < _entities.size(); i++)
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

    void EntityManager::remove(int id) 
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
        {
            EntityType i = it->second;
            int back = _entityList.back()->getID();

            std::swap(_entityList[back], _entityList.back());
            _entityList.pop_back();

            _entities[back] = i;
            _entities.erase(id);
        }
        TEMPEST_ERROR("This Entity with ID {0} does not exist.", id);
    }

    bool EntityManager::isRemoved(int id)
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

    bool EntityManager::isPlayer(int id) const
    {
        return(_playerID == id);
    }

    size_t EntityManager::size() const
    {
        return _entityList.size();
    }
}
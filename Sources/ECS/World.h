//
//  World.h
//  SGF
//
//  Created by DEPASSE Arthur on 14/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__World__
#define __SGF__World__

#include "Entity.h"
#include "System.h"
#include <unordered_map>
#include <typeindex>

namespace sgf
{
    class ISystem;
    class IWorld;
    
    class World
    {
    public:
        
        friend class ISystem;
        friend class IWorld;
        
        using indexType = unsigned int ;
        
        World();
        
        World(const World& rhs) = delete;
        World(World&& rhs) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;
        
        ~World()
        {
            removeAllSystems();
            removeAllEntities();
        }
        
        ////////////////////////////////////////////////////
        ////////////////////   SYSTEMS   ///////////////////
        ////////////////////////////////////////////////////
        
        template <typename SystemType>
        void addSystem(SystemType& system);
        
        template <typename SystemType>
        void removeSystem();
        
        template <typename SystemType>
        bool isSystemExisting() const;
        
        void addEntityToSystem(sgf::ISystem& sys, std::unique_ptr<sgf::Entity>& entity);
        
        void runSystems(const float elapsed);
        
        void removeAllSystems();
        
        ////////////////////////////////////////////////////
        ///////////////////// ENTITIES  ////////////////////
        ////////////////////////////////////////////////////
        
    public:
        
        void registerEntity(std::unique_ptr<sgf::Entity>& entity); //will take the ownership of the entity
        std::size_t getEntityCount() const;
        
        
    private:
        
        void removeEntity(const indexType & ID);
        void removeAllEntities();
        void reactiveEntity(const indexType & ID);
        void unactiveEntity(const indexType & ID);
        bool isActivated(const indexType & ID) const;
        
        
    private:
        
        std::unordered_map<size_t, ISystem&> _systems; //size_t represent the hash of the type_index
        std::size_t _systemCount;
        
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _activeEntities;
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _inactiveEntities;
        std::size_t _entityCount;
        
        
    };
    
    template <typename SystemType>
    void sgf::World::addSystem(SystemType &system)
    {
        //check the type is derived from sgf::System and that no any other system of that type is already registered in the world
        static_assert(std::is_base_of<sgf::ISystem, SystemType>::value, "Trying to register a system that do not derive from sgf::System");
        if(isSystemExisting<SystemType>()) throw sgf::Exception("System Type is already registered");
        
        // add it to the systems list
        auto ret = _systems.insert({std::type_index(typeid(SystemType)).hash_code(), system});
        if (!ret.second) throw sgf::Exception("Cannot register system in the world");
        
        ++_systemCount;
        
        
        
        //register all the entities it will manage
        for (auto it = _activeEntities.begin(); it != _activeEntities.end(); ++it)
        {
            addEntityToSystem(ret.first->second,it->second);
        }
    }
    
    template <typename SystemType>
    void sgf::World::removeSystem()
    {
        // check this system type is well registered in the world
        if (!isSystemExisting<SystemType>()) throw sgf::Exception("System Type doesn't exist and cannot be erased");
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        _systems.erase(_systems.find(index));
        --_systemCount;
    }
    
    template <typename SystemType>
    bool sgf::World::isSystemExisting() const
    {
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        auto it = std::find_if(_systems.begin(),
                               _systems.end(),
                               [&index](const std::unordered_map<size_t, sgf::ISystem& >::value_type &elem) -> bool
                               { return elem.first == index;}
                               );
        if ( it != _systems.end())
        return true;
        
        else return false;
        
    }
    
}

#endif /* defined(__SGF__World__) */

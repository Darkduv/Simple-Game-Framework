//
//  SystemBis.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 26/07/2015.
//  Copyright (c) 2015 DEPASSE Arthur. All rights reserved.
//

#include "System.h"
#include "World.h"

void sgf::IWorld::registerEntity(std::unique_ptr<sgf::Entity>& entity)
{
    _world.registerEntity(entity);
}
std::size_t sgf::IWorld::getEntityCount() const
{
    return _world.getEntityCount();
}
void sgf::IWorld::removeEntity(const indexType &ID)
{
    _world.removeEntity(ID);
}
void sgf::IWorld::removeAllEntities()
{
    _world.removeAllEntities();
}
void sgf::IWorld::reactiveEntity(const indexType &ID)
{
    _world.reactiveEntity(ID);
}
void sgf::IWorld::unactiveEntity(const indexType &ID)
{
    _world.unactiveEntity(ID);
}
bool sgf::IWorld::isActivated(const indexType &ID) const
{
    return _world.isActivated(ID);
}


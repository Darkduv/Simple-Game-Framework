//
//  MovementSystem.h
//  SGF
//
//  Created by DEPASSE Arthur on 03/03/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_MovementSystem_h
#define SGF_MovementSystem_h

#include "ECS.h"
#include "MyComponents.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include <utility>

class MovementSystem : public sgf::System<PositionComponent>
{
    
public:
    MovementSystem(sgf::World &world): sgf::System<PositionComponent>(world), speed(100)
    {}
    void run(sf::Time const& elapsed) override
    {
    auto time=elapsed.asSeconds();
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            auto &data= it->second.getComponent<PositionComponent>("pos")._data;
            
            data.x+=time*speed;
            data.y+=time*speed;
            
        }
    }
    
private:
    float speed;
    
};


class RenderSystem : public sgf::System<PositionComponent,CircleShapeComponent>
{
    
public:
    RenderSystem(sgf::World &world, sgf::Window& window): sgf::System<PositionComponent,CircleShapeComponent>(world), _window(window)
    {}
    void run(sf::Time const& elapsed) override
    {
        auto time=elapsed.asSeconds();
    
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            auto pos= it->second.getComponent<PositionComponent>("pos")._data;

            auto &shape =it->second.getComponent<CircleShapeComponent>("graph")._data;
            shape.setPosition(pos.x, pos.y);
            
            _window.draw(shape);
        }
    }
    
private:
    sgf::Window& _window;
    
};


#endif

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
#include "Messaging.h"
#include "MyComponents.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include <utility>
enum Side
{
    top,bot,right,left
};

struct PhysicEventListener
{
    virtual void bounced(sgf::Entity& entity, Side where) = 0;
};

struct PhysicEventContext
{
    enum pWhat {bounced} _whatHappenned;
    sgf::Entity* _entity;
    Side _where;
};

using PhysicEventSource = sgf::Messaging<PhysicEventListener,PhysicEventContext>;

struct UserEventListener
{
    virtual void changeColor(sf::Color color) = 0;
    virtual void changeSpeed(sf::Vector2f& speed) = 0;
};

struct UserEventContext
{
    sf::Event _event;
};

using UserEventSource = sgf::Messaging<UserEventListener,UserEventContext>;

class MovementSystem : public sgf::System<PositionComponent>, public PhysicEventListener
{
    
public:
    MovementSystem(sgf::World &world): sgf::System<PositionComponent>(world)
    {}
    virtual void run(float elapsed) override
    {
    ;
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            auto &data= it->second.getComponent<PositionComponent>("pos")._data;
            
            data.position.x+=elapsed*data.speed.x;
            data.position.y+=elapsed*data.speed.y;
            
        }
    }
    virtual void bounced(sgf::Entity& entity, Side where) //called when a PhysicEvent is launched
    {
        auto &data= entity.getComponent<PositionComponent>("pos")._data;

        switch (where) {
            case Side::top:
                data.speed.x*= -1;
                break;
            case Side::bot:
                data.speed.x*= -1;
                break;
            case Side::right:
                data.speed.y*= -1;
                break;
            case Side::left:
                data.speed.y*= -1;
                break;
            default:
                break;
        }
    }
};


class PhysicSystem : public sgf::System<PositionComponent>, public PhysicEventSource
{
public:
    PhysicSystem(sgf::World &world): sgf::System<PositionComponent>(world)
    {}
    virtual ~PhysicSystem() = default;
    virtual void run(float elapsed) override
    {
        
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            PhysicEventContext ctx;
            ctx._entity = &it->second;
            auto &data= it->second.getComponent<PositionComponent>("pos")._data;
            if (data.speed.x > 0 && data.position.x>1920-150) //moving down and close to the bottom wall
            {
                ctx._whatHappenned = PhysicEventContext::pWhat::bounced;
                ctx._where = Side::top;
                raiseEvent(ctx);
            }
            else if (data.speed.x < 0 && data.position.x<150) //moving up and close to the top wall
            {
                ctx._whatHappenned = PhysicEventContext::pWhat::bounced;
                ctx._where = Side::bot;
                raiseEvent(ctx);
            }
            else if (data.speed.y > 0 && data.position.y>1080-150) //moving right and close to the right wall
            {
                ctx._whatHappenned = PhysicEventContext::pWhat::bounced;
                ctx._where = Side::right;
                raiseEvent(ctx);
            }
            else if (data.speed.y < 0 && data.position.y<150) //moving left and close to the left wall
            {
                ctx._whatHappenned = PhysicEventContext::pWhat::bounced;
                ctx._where = Side::left;
                raiseEvent(ctx);
            }
            
        }
    }
    void dispatchEvent(PhysicEventListener &p,
                       const PhysicEventContext &context) override
    {
        switch (context._whatHappenned) {
            case PhysicEventContext::pWhat::bounced:
                p.bounced(*context._entity,context._where);
                break;
                
            default:
                break;
        }
    }
};



class RenderSystem : public sgf::System<PositionComponent,CircleShapeComponent>, public UserEventListener
{
    
public:
    RenderSystem(sgf::World &world, sgf::Window& window): sgf::System<PositionComponent,CircleShapeComponent>(world), _window(window)
    {}
    virtual void run(float elapsed) override
    {
    
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            auto pos= it->second.getComponent<PositionComponent>("pos")._data;

            auto &shape =it->second.getComponent<CircleShapeComponent>("graph")._data;
            shape.setPosition(pos.position.x, pos.position.y);
            
            _window.draw(shape);
        }
    }
    virtual void changeColor(sf::Color color)
    {
        for(auto it=_watchedEntity.begin(); it!=_watchedEntity.end(); it++)
        {
            auto &shape =it->second.getComponent<CircleShapeComponent>("graph")._data;
            shape.setFillColor(color);
        }
    }
    virtual void changeSpeed(sf::Vector2f& speed)
    {}
    
private:
    sgf::Window& _window;
    
};

class MyUserEvent : public UserEventSource
{
    virtual void dispatchEvent(UserEventListener &p,
                               const UserEventContext &context) override
    {
        switch (context._event.type) {
            case sf::Event::KeyPressed:
                switch (context._event.key.code)
            {
                case sf::Keyboard::B:
                    p.changeColor(sf::Color::Blue);
                    break;
                case sf::Keyboard::R:
                    p.changeColor(sf::Color::Red);
                    break;
                default:
                    break;
            }
            default:
                break;

        }
    }
public:
    void dispatch(const sf::Event& evt)
    {
        UserEventContext ctx;
        ctx._event = evt;
        raiseEvent(ctx);
    }
};


#endif

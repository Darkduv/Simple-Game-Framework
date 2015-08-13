//
//  MyComponents.h
//  SGF
//
//  Created by DEPASSE Arthur on 03/03/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_MyComponents_h
#define SGF_MyComponents_h

#include "Component.h"

#include <SFML/Graphics.hpp>

using HealthComponent  = sgf::Component<unsigned int>;
using RangeComponent = sgf::Component<unsigned int>;
struct Coords
{
    Coords(float xp, float yp, float xs, float ys): position(xp,yp), speed(xs,ys) {}
    sf::Vector2f position;
    sf::Vector2f speed;
};
using PositionComponent = sgf::Component<Coords>;
using CircleShapeComponent = sgf::Component<sf::CircleShape>;


#endif

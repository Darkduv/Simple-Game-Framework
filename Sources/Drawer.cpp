//
//  Drawer.cpp
//  Simple Game Framework
//
//  Created by DEPASSE Arthur on 10/08/2015.
//  Copyright (c) 2015 DEPASSE Arthur. All rights reserved.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <algorithm>
#include "Drawer.h"

namespace sgf
{
    enum Layer
    {
        Background = 1,
        Middle = 2,
        Foreground = 3
        
    };
    
    class Drawer
    {
    public:
        
        Drawer(sf::RenderWindow& window): _window(window), _toDraw()
        {_toDraw.reserve(100);}
        ~Drawer() = default;
        Drawer(Drawer const& rhs)               =delete;
        Drawer operator=(Drawer const& rhs)     =delete;
        Drawer operator=(Drawer &&rhs)          =delete;
        Drawer(Drawer&& rhs)                    =delete;
        
        
        void draw(const sf::Drawable &drawable, sgf::Layer layer = sgf::Layer::Middle)
        {
            _toDraw.push_back(std::make_pair(&drawable, layer));
        }
        void flushRenderQueue()
        {
            _toDraw.clear();
        }
        
    private:
        
        void render()
        {
            std::sort(std::begin(_toDraw), std::end(_toDraw),
                      [](const std::vector<std::pair<const sf::Drawable*,sgf::Layer>>::value_type &elem,const std::vector<std::pair<const sf::Drawable*,sgf::Layer>>::value_type &elem2) -> bool
                      { return elem.second < elem2.second; }
                      );
            for(auto &i: _toDraw)
            {
                _window.draw(*(i.first));
            }
        }
        sf::RenderWindow &_window;
        std::vector<std::pair<const sf::Drawable*,sgf::Layer>> _toDraw;
    };
    
    
}
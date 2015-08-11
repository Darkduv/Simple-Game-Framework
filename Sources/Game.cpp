//
//  Game.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Game.h"


sgf::Game::Game(const std::string& title, unsigned int width, unsigned int height, unsigned int style) : _stateManager(), _window(title,width,height,style)
{}

sgf::Game::~Game()
{}

sgf::Window& sgf::Game::getWindow()
{
    return _window;
}

void sgf::Game::exec()
{
    init();
    
    _stateManager.Init();
    
    load();
    
    sf::Clock clock;
    
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            _stateManager.HandleEvents(event);
        }
        
        
        _stateManager.Update(clock.restart().asSeconds());
        
        _stateManager.Draw(_window);
        
        _window.clear();
        
        _window.display();
        
    }
    
    unload();
    
}




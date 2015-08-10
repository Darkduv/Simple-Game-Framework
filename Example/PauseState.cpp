//
//  PauseState.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "PauseState.h"


PauseState::PauseState(sgf::StateManager& stateMng,sgf::Game& game): sgf::IState(stateMng,game), text(), font()
{
    font.loadFromFile("media/font/font.ttf");
    
    text.setFont(font);
    
    text.setString("PauseState");
    
    text.setCharacterSize(40);
}

void PauseState::Init()
{
    
}
void PauseState::Cleanup()
{
    
}

void PauseState::Pause()
{
    
}
void PauseState::Resume()
{
    
}


void PauseState::HandleEvents(sf::Event const& evt)
{
    switch (evt.type) {
        case sf::Event::Closed:
            _game.getWindow().close();
            break;
            
        case sf::Event::KeyPressed:
            switch (evt.key.code)
        {
            case sf::Keyboard::P:
                PopState();
                break;
            case sf::Keyboard::Escape:
                _game.getWindow().close();
                break;
            default:
            break;
        }
            break;
        default:
        break;
    }
}
void PauseState::Update(sf::Time const& elapsed)
{
}
void PauseState::Draw(sgf::Window& window)
{
    window.draw(text);
}

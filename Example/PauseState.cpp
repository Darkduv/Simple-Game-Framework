//
//  PauseState.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "PauseState.h"


PauseState::PauseState(sgf::StateManager& stateMng): sgf::IState(stateMng), text(), font()
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


void PauseState::HandleEvents(sgf::Game &game,sf::RenderWindow& window, sf::Event const& evt)
{
    switch (evt.type) {
        case sf::Event::Closed:
            window.close();
            break;
            
        case sf::Event::KeyPressed:
            switch (evt.key.code)
        {
            case sf::Keyboard::P:
                PopState();
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
            default:
            break;
        }
            break;
        default:
        break;
    }
}
void PauseState::Update(sgf::Game &game, sf::Time const& elapsed)
{
}
void PauseState::Draw(sgf::Game &game,sf::RenderWindow& window)
{
    window.draw(text);
}

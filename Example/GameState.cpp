//
//  GameState.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "GameState.h"


GameState::GameState(sgf::StateManager& stateMng, sgf::Game &game): sgf::IState(stateMng,game), text(), font()
{
    font.loadFromFile("media/font/font.ttf");
    
    text.setFont(font);
    
    text.setString("GameState");
    
    text.setCharacterSize(40);
}

void GameState::Init()
{
    
}
void GameState::Cleanup()
{
    
}

void GameState::Pause()
{
    
}
void GameState::Resume()
{
    
}


void GameState::HandleEvents(sf::Event const& evt)
{
    switch (evt.type) {
        case sf::Event::Closed:
            _game.getWindow().close();
            break;
            
        case sf::Event::KeyPressed:
            switch (evt.key.code)
            {
            case sf::Keyboard::P:
                PushState(std::make_unique<PauseState>(_stateMng,_game));
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
void GameState::Update(sf::Time const& elapsed)
{
}
void GameState::Draw(sgf::Window& window)
{
    window.draw(text);
}
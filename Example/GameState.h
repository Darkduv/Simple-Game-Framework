//
//  GameState.h
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__GameState__
#define __SGF__GameState__

#include "MyGame.h"
#include <SFML/Graphics.hpp>
#include "PauseState.h"
#include "Logger.h"


class MyGame;

class GameState: public sgf::IState
{
public:
    
    GameState(sgf::StateManager& stateMng, sgf::Game& game);
    virtual ~GameState(){}
    
    virtual void Init();
    virtual void Cleanup();
    
    virtual void Pause();
    virtual void Resume();
    
    virtual void HandleEvents(sf::Event const& evt);
    virtual void Update(float elapsed);
    virtual void Draw(sgf::Window& window);
    
protected:
    
    GameState(const GameState& rhs)=delete;
    void operator=(const GameState& rhs)=delete;
    
private:
    sf::Text text;
    sf::Font font;
    
};

#endif /* defined(__SGF__GameState__) */

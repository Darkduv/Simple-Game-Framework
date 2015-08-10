//
//  IntroState.h
//  SGF
//
//  Created by DEPASSE Arthur on 04/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__IntroState__
#define __SGF__IntroState__

#include "MyGame.h"
#include "GameState.h"
#include "StandardRessourceLoader.h"


#include "Logger.h"

#include "Gui.h"


#include "ECS.h"

#include "MyComponents.h"
#include "MovementSystem.h"


#include <SFML/Graphics.hpp>

class MyGame;

class IntroState: public sgf::IState
{
public:
    
    IntroState(sgf::StateManager& stateMng, sgf::Game& game, int width, int height);
    virtual ~IntroState(){}
    
    virtual void Init();
    virtual void Cleanup();
    
    virtual void Pause();
    virtual void Resume();
    
    virtual void HandleEvents(sf::Event const& evt);
    virtual void Update(sf::Time const& elapsed);
    virtual void Draw(sgf::Window& window);
    
protected:
    
    IntroState(const IntroState& rhs)=delete;
    void operator=(const IntroState& rhs)=delete;
    
private:
    
    sgf::TextureLoader _texLoader;
    sgf::SpriteLoader _spriteLoader;

    
    sgf::MusicLoader _musicLoader;
    sf::Music* music;
    
    sgf::gui::Button jouer;
    sgf::gui::Button quitter;
    sgf::gui::Button reglages;
    
    sgf::World world;
    
    int _width;
    int _height;
    
    std::vector< std::unique_ptr<sgf::ISystem> > _systems;
    

    
};

#endif /* defined(__SGF__IntroState__) */

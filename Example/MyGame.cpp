//
//  MyGame.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 03/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "MyGame.h"

MyGame::MyGame(const std::string& title, unsigned int width, unsigned int height, unsigned int style) :
                sgf::Game(title, width, height, style), _width(width), _height(height)

{
    _stateManager.PushState(std::make_unique<IntroState>(_stateManager, *this, _width, _height));
}

MyGame::~MyGame()
{
    
}

void MyGame::init()
{
    
}
void MyGame::load()
{

}
void MyGame::unload()
{
    _stateManager.Cleanup();
}



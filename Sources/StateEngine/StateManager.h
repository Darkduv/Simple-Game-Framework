//
//  StateManager.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__StateManager__
#define __SGF__StateManager__

#include <stack>
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Exception.h"
#include "Logger.h"
#include "State.h"

namespace sgf
{
    
    class StateManager
    {
    public:
        
        typedef std::unique_ptr<sgf::IState> StatePtr;
        StateManager();
        virtual ~StateManager();
    
        virtual void Init();
        virtual void Cleanup();
    
        void PushState(StatePtr&& state);  // will take the ownership of the given State
        void PopState();
        void PopAndPush(StatePtr&& state); // will take the ownership of the given State
    
        void HandleEvents(const sf::Event &evt);
        void Update(float elapsed);
        void Draw(sgf::Window& window);
    
    protected:
        
        std::unique_ptr<sgf::IState>& currentState(); //fast access;
    
        std::stack<StatePtr> _states; //stack of States
        
    private:
        
        StateManager(StateManager const& rhs)=delete;
        void operator=(StateManager const& rhs)=delete;
        
    
    };
    
    

}



#endif /* defined(__SGF__StateManager__) */

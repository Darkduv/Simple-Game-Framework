//
//  Messaging.h
//  Simple Game Framework
//
//  Created by DEPASSE Arthur on 13/08/2015.
//  Copyright (c) 2015 DEPASSE Arthur. All rights reserved.
//  THANKS YOU DRDOBBS FOR YOUR HELP ON THIS ONE :D

#ifndef __Simple_Game_Framework__Messaging__
#define __Simple_Game_Framework__Messaging__

#include "Messaging.h"
#include <vector>

namespace sgf
{
    // A MutexHolder that do not synchronize
    class NoSynchronization
    {
    public:
        void lock() {}
        void unlock() {}
    };
    
    class Synchronization
    {
    public:
        void lock() {/*do some stuff*/}
        void unlock() {/*do some stuff*/}
    };
    
    // the interface of the wrapper to back-end,
    // synchronized collection of pointers
    
    template
    <
    class Listener,
    class Mutex,
    class BagType
    >
    class ListenersCollection
    {
        // this is a helper class that locks a given mutex
        // and unlocks when exiting the scope
        class MutexHolder
        {
        public:
            MutexHolder(Mutex& mutex):_mutexToLock(mutex)
            {
                _mutexToLock.lock();
            }
            ~MutexHolder()
            {
                _mutexToLock.unlock();
            }
        private:
            Mutex _mutexToLock;
        };
        
    public:
        
        void add(Listener *p)
        {
            MutexHolder m(mutex_);
            bag_.push_back(p);
        }
        void remove(Listener *p)
        {
            MutexHolder m(mutex_);
            bag_.erase(p);
        }
        
        BagType getFrozen() const
        {
            return bag_;
        }
        
    private:
        
        BagType bag_;
        Mutex mutex_;
    };
    
    template
    <
    class Listener,
    typename Context = int,
    class Mutex = sgf::NoSynchronization,
    class BagType = std::vector<Listener*>
    >
    class Messaging
    {
    public:
        virtual ~Messaging<Listener,Context,Mutex,BagType>() = default;
        // registers the listener
        // listeners registered more than once will be notified
        // once for each registration
        void addListener(Listener& listener)
        {
            listeners_.add(&listener);
        }
        
        // unregisters the listener
        // it doesn't hurt if it's not already registered
        // multiply registered listeners should also multiply
        // unregister themselves
        void removeListener(Listener& listener)
        {
            listeners_.remove(&listener);
        }
        
    protected:
        
        // this method should be called by the derived class
        // to trigger event dispatching
        void raiseEvent(const Context &context)
        {
            using iterator = typename BagType::iterator;
            BagType frozen(listeners_.getFrozen());
            iterator it;
            iterator itend = frozen.end();
            
            for (it = frozen.begin(); it != itend; ++it)
            {
                Listener* p = static_cast<Listener*>(*it);
                dispatchEvent(*p, context);
            }
        }
        
        // this is intended to be overriden in a derived class
        // and is responsible for the actual dispatching
        // this method is called for every registered listener
        // (once for each registration)
        // the overriding method should call the listener,
        // using (or not) the context as a clue
        virtual void dispatchEvent(Listener& listener,
                                   const Context &context) = 0;
        
    private:
        
        // the synchronized container for keeping pointers
        // to listener objects
        ListenersCollection<Listener, Mutex, BagType> listeners_;
    };
}

#endif /* defined(__Simple_Game_Framework__Messaging__) */

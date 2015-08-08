//
//  Component.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Component__
#define __SGF__Component__

#include <string>

namespace sgf
{
    class IComponent
    {
    public:
        
        IComponent(const std::string &ID) : _id(ID)
        {}
        
        IComponent(IComponent&& rhs) : _id(rhs._id)
        {}
        
        IComponent (IComponent const& rhs)              =delete;
        IComponent& operator=(const IComponent &rhs)    =delete;
        IComponent& operator=(IComponent && rhs)        =delete;
        virtual ~IComponent()                           =default;
        
        const std::string &getId() const { return _id; }
   
    protected:
        
        const std::string _id;
        
    };
    
    template <class DataType>
    struct Component : public sgf::IComponent
    {
        template<class ... Args>
        Component(const std::string &ID, Args&&... args) : sgf::IComponent(ID), _data(std::forward<Args>(args)...)
        {}
        Component(Component&& rhs) : IComponent(rhs._id), _data(rhs._data)
        {}
        Component (Component const& rhs)                =delete;
        Component& operator=(const Component &rhs)      =delete;
        Component& operator=(Component && rhs)          =delete;
        virtual ~Component()                            =default;
        
        DataType _data;
    };
}

#endif /* defined(__SGF__Component__) */

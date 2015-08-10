//
//  Window.h
//  Simple Game Framework
//
//  Created by DEPASSE Arthur on 10/08/2015.
//  Copyright (c) 2015 DEPASSE Arthur. All rights reserved.
//

#ifndef __Simple_Game_Framework__Window__
#define __Simple_Game_Framework__Window__

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <algorithm>

namespace sgf
{
    enum Layer
    {
        Background = 1,
        Middle = 2,
        Foreground = 3
        
    };
    
    class Window
    {
    public:
        Window(const std::string &title, unsigned int width, unsigned int height, unsigned int style = sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings()): _window(sf::VideoMode(width,height),title, style, settings), _toDraw()
        {_toDraw.reserve(100);}
        ~Window() = default;
        Window(Window const& rhs)               =delete;
        Window operator=(Window const& rhs)     =delete;
        Window operator=(Window &&rhs)          =delete;
        Window(Window&& rhs)                    =delete;
        
        auto getSize()const
        {
            return _window.getSize();
        }
        auto capture()const
        {
            return _window.capture();
        }
        auto getSettings() const
        {
            return _window.getSettings();
        }
        auto getPosition() const
        {
            return _window.getPosition();
        }
        auto getView() const
        {
            return _window.getView();
        }
        auto getDefaultView() const
        {
            return _window.getDefaultView();
        }
        auto getViewport(const sf::View &view) const
        {
            return _window.getViewport(view);
        }
        void draw(const sf::Drawable &drawable, sgf::Layer layer = sgf::Layer::Middle)
        {
            _toDraw.push_back(std::make_pair(&drawable, layer));
        }
        void clear(const sf::Color &color=sf::Color(0,0,0,255))
        {
            _window.clear(color);
        }
        void display()
        {
            std::sort(std::begin(_toDraw),
                      std::end(_toDraw),
                      [](const VectorType::value_type &elem1,const VectorType::value_type &elem2) -> bool
                      { return elem1.second < elem2.second; }
                      );
            
            for(auto &i: _toDraw)
            {
                _window.draw(*(i.first));
            }
            
            _window.display();
            
            flushRenderQueue();
        }
        
        
        auto pollEvent(sf::Event &event)
        {
            return _window.pollEvent(std::forward<sf::Event&>(event));
        }
        auto waitEvent(sf::Event &event)
        {
            return _window.waitEvent(std::forward<sf::Event&>(event));
        }
        
        
        void setPosition(const sf::Vector2i &position)
        {
            _window.setPosition(std::forward<const sf::Vector2i&>(position));
        }
        void setSize(const sf::Vector2u &size)
        {
            _window.setSize(std::forward<const sf::Vector2u&>(size));
        }
        void setTitle(const std::string &title)
        {
            _window.setTitle(std::forward<const std::string&>(title));
        }
        void setIcon(unsigned int width, unsigned int height, const sf::Uint8 *pixels)
        {
            _window.setIcon(width, height, pixels);
        }
        void setVisible(bool visible)
        {
            _window.setVisible(visible);
        }
        void setVerticalSyncEnabled(bool enabled)
        {
            _window.setVerticalSyncEnabled(enabled);
        }
        void setMouseCursorVisible(bool visible)
        {
            _window.setMouseCursorVisible(visible);
        }
        void setKeyRepeatEnabled(bool enabled)
        {
            _window.setKeyRepeatEnabled(enabled);
        }
        void setFramerateLimit(unsigned int limit)
        {
            _window.setFramerateLimit(limit);
        }
        void setJoystickThreshold(float threshold)
        {
            _window.setJoystickThreshold(threshold);
        }
        bool setActive(bool active=true) const
        {
            return _window.setActive(active);
        }
        void setView(const sf::View &view)
        {
            _window.setView(view);
        }
        bool isOpen()
        {
            return _window.isOpen();
        }
        void close()
        {
            _window.close();
        }
        void flushRenderQueue()
        {
            _toDraw.clear();
        }
    private:
        
        using VectorType = std::vector<std::pair<const sf::Drawable*,sgf::Layer>>;
        

        
        sf::RenderWindow _window;
        VectorType _toDraw;
    };
    
    
}

#endif /* defined(__Simple_Game_Framework__Window__) */

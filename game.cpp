#include "game.hpp"
#include "playState.hpp"
#include "sprite.hpp"
#include <iostream>
#include <ctime>

void gameClass::initialize()
{
    window.create(sf::VideoMode(630, 540), "SFML window");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    gameStateStack.setWindow(&window);
    gameStateStack.set(new playStateClass());
    spriteClass::initText();
}

void gameClass::run()
{
    while(window.isOpen())
    {
        gameStateStack.update();
        if(gameStateStack.getChange())
        {
            gameStateStack.setChange(false);
            gameStateStack.update();
            gameStateStack.draw();
        }
        else
        {
            gameStateStack.draw();
        }
        window.display();
    }
}


#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "gameStateStack.hpp"

class gameClass
{
public:
    void initialize();
    void run();
private:
    sf::RenderWindow window;
    gameStateStackClass gameStateStack;
};

#endif


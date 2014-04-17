#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "gameState.hpp"

class endStateClass : public gameStateClass
{
public:
    endStateClass(std::string newWinner);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void drawText(std::string text, int posX, int posY);
private:
    std::string winner;
    sf::Font font;
};

#endif

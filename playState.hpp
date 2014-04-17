#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameState.hpp"
#include "IA.hpp"

class playStateClass : public gameStateClass
{
public:
    playStateClass();
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void drawSprite(sf::Texture& sprite, int posX, int posY);
    void placeToken(typeCase color, int numberColumn);
    typeCase checkWin();
    void checkEndGame();
private:
    std::map<poseCase, typeCase> mapLevel;
    bool lastTokenIsBlue;
    int nbCoup;
    poseCase lastPose;
    IAclass IAgame;
};

#endif

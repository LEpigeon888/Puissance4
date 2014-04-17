#include "playState.hpp"
#include "endState.hpp"
#include "sprite.hpp"
#include "gameStateStack.hpp"

playStateClass::playStateClass()
{
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            mapLevel[poseCase(i, j)] = VIDE;
        }
    }
    lastTokenIsBlue = false;
    lastPose = poseCase(-1, -1);
    IAgame.setColor(ROUGE);
}

void playStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
}

void playStateClass::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
            break;
        }
        if(!lastTokenIsBlue)
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    placeToken(BLEU, event.mouseButton.x / 90);
                }
            }
        }
        else
        {
            placeToken(ROUGE, IAgame.calcCoup(mapLevel, 5));
        }
    }
}

void playStateClass::draw()
{
    window->clear(sf::Color::White);
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            if(mapLevel[poseCase(i, j)] == VIDE)
            {
                drawSprite(spriteClass::getImage("casevide"), i * 90, j * 90);
            }
            else if(mapLevel[poseCase(i, j)] == BLEU)
            {
                drawSprite(spriteClass::getImage("casebleu"), i * 90, j * 90);
            }
            else if(mapLevel[poseCase(i, j)] == ROUGE)
            {
                drawSprite(spriteClass::getImage("caserouge"), i * 90, j * 90);
            }
        }
    }
}

void playStateClass::drawSprite(sf::Texture& sprite, int posX, int posY)
{
    sf::Sprite tmpSprite;
    tmpSprite.setTexture(sprite);
    tmpSprite.setPosition(posX, posY);
    window->draw(tmpSprite);
}

void playStateClass::placeToken(typeCase color, int numberColumn)
{
    for(int i = 5; i >= 0; --i)
    {
        if(mapLevel[poseCase(numberColumn, i)] == VIDE)
        {
            mapLevel[poseCase(numberColumn, i)] = color;
            lastPose = poseCase(numberColumn, i);
            lastTokenIsBlue = !lastTokenIsBlue;
            ++nbCoup;
            checkEndGame();
            return;
        }
    }
}

typeCase playStateClass::checkWin()
{
    if(nbCoup < 7)
    {
        return VIDE;
    }

    for(int i = lastPose.first - 1; i < lastPose.first + 2; ++i)
    {
        for(int j = lastPose.second - 1; j < lastPose.second + 2; ++j)
        {
            if((i == lastPose.first && j == lastPose.second) || mapLevel[poseCase(i, j)] == VIDE)
            {
                continue;
            }

            if(mapLevel[poseCase(i, j)] == mapLevel[lastPose])
            {
                int tmpX = i;
                int tmpY = j;
                int numberToken = 1;
                do
                {
                    ++numberToken;
                    tmpX = tmpX - (lastPose.first - i);
                    tmpY = tmpY - (lastPose.second - j);
                }
                while(mapLevel[poseCase(tmpX, tmpY)] == mapLevel[lastPose]);

                tmpX = lastPose.first;
                tmpY = lastPose.second;
                --numberToken;
                do
                {
                    ++numberToken;
                    tmpX = tmpX + (lastPose.first - i);
                    tmpY = tmpY + (lastPose.second - j);
                }
                while(mapLevel[poseCase(tmpX, tmpY)] == mapLevel[lastPose]);

                if(numberToken > 3)
                {
                    return mapLevel[lastPose];
                }
            }
        }
    }

    return VIDE;
}

void playStateClass::checkEndGame()
{
    typeCase winner = checkWin();
    if(winner != VIDE)
    {
        parent->add(new endStateClass((winner == BLEU ? "Bleu" : "Rouge")));
    }
    else
    {
        bool mapLevelIsFull = true;
        for(int i = 0; i < 7; ++i)
        {
            for(int j = 0; j < 6; ++j)
            {
                if(mapLevel[poseCase(i, j)] == VIDE)
                {
                    mapLevelIsFull = false;
                    break;
                }
            }
            if(mapLevelIsFull == false)
            {
                break;
            }
        }

        if(mapLevelIsFull)
        {
            parent->add(new endStateClass("Egalite"));
        }
    }
}

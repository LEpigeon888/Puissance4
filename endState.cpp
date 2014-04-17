#include "endState.hpp"
#include "gameStateStack.hpp"
#include "playState.hpp"

endStateClass::endStateClass(std::string newWinner)
{
    winner = newWinner;
    font.loadFromFile("cour.ttf");
}

void endStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
}

void endStateClass::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
            break;
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                parent->set(new playStateClass());
            }
        }
    }
}

void endStateClass::draw()
{
    parent->drawOld();
    if(winner == "Egalite")
    {
        drawText("Personne n'a gagné", 50, 50);
    }
    else
    {
        drawText(winner + " a gagné", 100, 50);
    }
}

void endStateClass::drawText(std::string text, int posX, int posY)
{
    sf::Text message;
    message.setCharacterSize(50);
    message.setColor(sf::Color::Green);
    message.setFont(font);
    message.setPosition(posX, posY);
    message.setString(text);

    window->draw(message);
}

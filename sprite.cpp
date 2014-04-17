#include "sprite.hpp"

sf::Texture spriteClass::image[3];

void spriteClass::initText()
{
    image[0].loadFromFile("casevide.png");
    image[1].loadFromFile("casebleu.png");
    image[2].loadFromFile("caserouge.png");
}

sf::Texture& spriteClass::getImage(std::string nameImage)
{
    if(nameImage == "casevide")
        return image[0];
    else if(nameImage == "casebleu")
        return image[1];
    else if(nameImage == "caserouge")
        return image[2];

    return image[0];
}


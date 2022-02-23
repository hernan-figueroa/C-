#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include"Math.h"

class Element
{
private:

    sf::Texture texture;

public:
    sf::Sprite sprite;
    Element(std::string element, int width,int height,float xScale, float yScale)
    {
        setTexture(element);
        this->sprite.setTexture(texture);
        this->sprite.setTextureRect(sf::IntRect(0,0,width,height));
        this->sprite.setScale(sf::Vector2f(xScale,yScale));
        setRandomPosition();
    }
    Element(std::string element, int width,int height,float xScale, float yScale,sf::Vector2f position)
    {
        setTexture(element);
        this->sprite.setTexture(texture);
        this->sprite.setTextureRect(sf::IntRect(0,0,width,height));
        this->sprite.setScale(sf::Vector2f(xScale,yScale));
        sprite.setPosition(position);
    }
    ~Element() {}

    void setTexture(std::string element){

        this->texture.loadFromFile(element);

    }
    void setRandomPosition()
    {
        sprite.setPosition(Math::RandomPosition());
    }

    sf::Vector2f getPosition()
    {
        return sprite.getPosition();
    }
    sf::Sprite getSprite()
    {
        return sprite;
    }

    void Draw(sf::RenderWindow& window)
    {

        window.draw(sprite);
    }
};

#endif // ELEMENT_H_INCLUDED

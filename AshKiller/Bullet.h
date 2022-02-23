#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>


class Bullet
{
private:
    ///sf::RectangleShape rectangleShape;
    sf::Texture bala;
    ///
    sf::Vector2f direction;
    float m_speed;
public:
    sf::Sprite spriteBala;

public:

    Bullet();
    ~Bullet();

    void Initialize(const sf::Vector2f& position, const sf::Vector2f& target,std::string balaType);
    void Update(double deltaTime);
    void Draw(sf::RenderWindow& window);

    const sf::FloatRect GetGlobalBounds()
    {
        return spriteBala.getGlobalBounds();
    }
};

#endif // BULLET_H_INCLUDED

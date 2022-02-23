#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED


#include <SFML/Graphics.hpp>


class Math
{
public:
    static sf::Vector2f NormalizeVector(sf::Vector2f vector);
    static sf::Vector2f RandomPosition();
    static bool DidRectCollide(sf::FloatRect rect1, sf::FloatRect rect2);
    static void PositionView(sf::RenderWindow& window,sf::Vector2f& positionView, sf::Vector2f& playerPos);
};


#endif // MATH_H_INCLUDED

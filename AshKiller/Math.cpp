#include <iostream>

#include "Math.h"


sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;

    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;

    return normalizedVector;
}


sf::Vector2f Math::RandomPosition()
{
    sf::Vector2f randomPosition = {static_cast<float>(rand() % static_cast<int>(1200)+100),
                                   static_cast<float>(rand() % static_cast<int>(450)+100)
                                  };

    return randomPosition;
}

bool Math::DidRectCollide(sf::FloatRect rect1, sf::FloatRect rect2)
{
    if (rect1.left + rect1.width > rect2.left &&
            rect2.left + rect1.width > rect1.left &&
            rect2.top + rect2.height > rect1.top &&
            rect1.top + rect1.height > rect2.top)
        return true;

    return false;
}

void Math::PositionView(sf::RenderWindow& window,sf::Vector2f& positionView, sf::Vector2f& playerPos){

            if(playerPos.x + 10 >window.getSize().x/2)
        {
            if(playerPos.x + 10 >1200)
                positionView.x = 1200;
            else
                positionView.x = playerPos.x + 10;
        }
        else
            positionView.x = window.getSize().x/2;

}

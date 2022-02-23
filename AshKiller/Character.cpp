#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Character
{

public:
    enum class AnimationIndex
    {
        WalkingUp,
        WalkingDown,
        WalkingLeft,
        WalkingRight,
        Count
    };
    sf::Texture texture;
    sf::Sprite sprite;

    float speed;
    float damage;
    sf::Vector2f pos;
    int health;
    int points = 0;
    std::string nombre;
    std::string pathImg;


    void ChangeHealth(float hp)
    {
        health += hp;
    }

};

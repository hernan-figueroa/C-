#ifndef SKELETON_H_INCLUDED
#define SKELETON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include"Character.cpp"
#include"Animation.h"
#include "Bullet.h"


class Skeleton : public Character
{

private:

    sf::Text healthText;
    sf::Font font;
    int enemyType;


    Animation animations[int(AnimationIndex::Count)];
    AnimationIndex currentAnimation = AnimationIndex::WalkingDown;

public:
    int t=0;
    bool dead = false;
    sf::Vector2f direction;
public:
    Skeleton(int type);
    ~Skeleton();
    void EnemyType1( );
    void EnemyType2( );
    void EnemyType3( );
    void directionPlayer(sf::Vector2f& target);
    void directionRandom();

    void ChangeHealth(float hp);
    void Load();
    void Update(double deltaTime,sf::Vector2f& target, int& points);
    void Draw(sf::RenderWindow& window);
};

#endif // SKELETON_H_INCLUDED

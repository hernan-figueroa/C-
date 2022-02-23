#include <SFML/Graphics.hpp>
#include "Skeleton.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Math.h"
#include"Animation.h"

Skeleton::Skeleton(int type )
{
    enemyType=type;
    direction = Math::NormalizeVector(Math::RandomPosition() - sprite.getPosition());
    sprite.setPosition(Math::RandomPosition());
    switch(enemyType)
    {
    case 1:
        EnemyType1();
        break;
    case 2:
        EnemyType2();
        break;
    case 3:
        EnemyType3();
        break;
    }
}

Skeleton::~Skeleton()
{

    delete(this);
}

void Skeleton::EnemyType1( )
{
    pathImg = "img/skeleton.png";
    sprite.setTextureRect({0,0,32,64});
    animations[int(AnimationIndex::WalkingDown)] = Animation(128,0,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingRight)] = Animation(128,128,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingLeft)] = Animation(128,64,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingUp)] = Animation(128,192,32,64,pathImg,3);
    speed = 0.98f;
    damage = -0.1;
    health = 5;

}
void Skeleton::EnemyType2( )
{
    pathImg = "img/skeleton.png";
    sprite.setTextureRect({0,0,32,64});
    animations[int(AnimationIndex::WalkingDown)] = Animation(0,0,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingRight)] = Animation(0,128,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingLeft)] = Animation(0,64,32,64,pathImg,3);
    animations[int(AnimationIndex::WalkingUp)] = Animation(0,192,32,64,pathImg,3);
    speed = 0.7f;
    damage = -0.5;
    health = 15;
}

void Skeleton::EnemyType3( )
{
    pathImg = "img/enemigoFinal.png";
    sprite.setTextureRect({0,0,32,48});
    animations[int(AnimationIndex::WalkingDown)] = Animation(0,192,32,48,pathImg,3);
    animations[int(AnimationIndex::WalkingRight)] = Animation(0,288,32,48,pathImg,3);
    animations[int(AnimationIndex::WalkingLeft)] = Animation(0,240,32,48,pathImg,3);
    animations[int(AnimationIndex::WalkingUp)] = Animation(0,336,32,48,pathImg,3);
    speed = 0.8f;
    damage = -1.f;
    sprite.setScale(1.1,1.1);
    health = 20;


}

void Skeleton::ChangeHealth(float hp)
{
    health += hp;
    healthText.setString(std::to_string(health));
}

void Skeleton::Load()
{
    if (font.loadFromFile("font/Homer_Simpson.ttf"))
    {
        healthText.setFont(font);
        healthText.setScale(0.8f,0.8f);
        healthText.setString(std::to_string(health));
    }
    else
    {
        std::cout << "Failed to load Arial.ttf font in Assets" << std::endl;
    }

    sprite.scale(sf::Vector2f(1, 1));

}
void Skeleton::directionRandom()
{
    if (sprite.getGlobalBounds().left <= 0.f || sprite.getGlobalBounds().left >= 1570 ||
            sprite.getGlobalBounds().top<= 100.f || sprite.getGlobalBounds().top >= 540)
    {
        direction = Math::NormalizeVector(Math::RandomPosition() - sprite.getPosition());
    }
}

void Skeleton::directionPlayer(sf::Vector2f& target)
{
    direction = Math::NormalizeVector(target - sprite.getPosition());
}
void Skeleton::Update(double deltaTime,sf::Vector2f& target, int& points )
{
    if(enemyType==3)
        directionPlayer(target);
    else
        directionRandom();


    if(direction.x >0.0f)
    {
        currentAnimation = AnimationIndex::WalkingRight;
    }
    else if(direction.x <0.0f)
    {
        currentAnimation = AnimationIndex::WalkingLeft;
    }
    else if(direction.y <0.0f)
    {
        currentAnimation = AnimationIndex::WalkingUp;
    }
    else if(direction.y >0.0f)
    {
        currentAnimation = AnimationIndex::WalkingDown;
    }
    pos= sprite.getPosition() + direction * speed * (float)deltaTime;

    animations[int(currentAnimation)].Update(deltaTime);
    animations[int(currentAnimation)].ApplyToSprite(sprite);

    if (health > 0)
    {
        sprite.setPosition(pos );
        healthText.setPosition(sprite.getPosition().x-10,sprite.getPosition().y);
    }
    else
    {
        dead= true;
        points+=enemyType;
    }

}

void Skeleton::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(healthText);
}

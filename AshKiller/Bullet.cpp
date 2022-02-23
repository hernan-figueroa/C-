#include <iostream>
#include <string>
#include <cstdlib>
#include "Bullet.h"
#include "Math.h"


Bullet::Bullet() :
    m_speed(5)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, std::string balaType)
{

    ///--------------------
    if(!bala.loadFromFile(balaType))
    {
        std::cout << "pokebola texture not loaded!" << std::endl;
    }
    spriteBala.setTexture(bala);

    spriteBala.setScale(0.20f,0.20f);
    spriteBala.setTextureRect(sf::IntRect(0,0,95,123));
    spriteBala.setPosition(position);
    direction = Math::NormalizeVector(target - position);
    ///-------------------------
}

void Bullet::Update(double deltaTime)
{
    spriteBala.setPosition(spriteBala.getPosition() + direction * m_speed * (float)deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(spriteBala);
}

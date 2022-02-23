#include "Player.h"
#include <iostream>
#include "Math.h"



Player::Player() :
   maxFireRate(40), fireRateTimer(0)
{
    pathImg = "img/player.png";
    health =100;
    damage = -1.0;
    speed = 1.f;
    sprite.setTextureRect({0,0,64,64});
    animations[int(AnimationIndex::WalkingDown)] = Animation(0,0,64,64,pathImg,4);
    animations[int(AnimationIndex::WalkingRight)] = Animation(0,128,64,64,pathImg,4);
    animations[int(AnimationIndex::WalkingLeft)] = Animation(0,64,64,64,pathImg,4);
    animations[int(AnimationIndex::WalkingUp)] = Animation(0,192,64,64,pathImg,4);
}

Player::~Player()
{
}


void Player::Load()
{

    pos = sf::Vector2f(0, 400);

    sprite.scale(sf::Vector2f(0.8f, 0.8f));

}

void Player::SetDirection(const sf::Vector2f& dir)
{

    vel = dir * speed;

    if(dir.x >0.0f)
    {
        currentAnimation = AnimationIndex::WalkingRight;
    }
    else if(dir.x <0.0f)
    {
        currentAnimation = AnimationIndex::WalkingLeft;
    }
    else if(dir.y <0.0f)
    {
        currentAnimation = AnimationIndex::WalkingUp;
    }
    else if(dir.y >0.0f)
    {
        currentAnimation = AnimationIndex::WalkingDown;
    }
}

void Player::Update(sf::RenderWindow& window,double deltaTime, std::vector<Skeleton*>& enemigos, sf::Vector2f& mousePosition, Element& botiquin,Element&pokebolaGolden)
{
    sf::Vector2f dir = {0.0f,0.0f};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x<=1546)
        dir.x +=1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x>0)
        dir.x -=1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y<=546)
        dir.y +=1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y>128)
        dir.y -=1.0f;

    SetDirection(dir);

    /// Cambia de frame de la imagen solo si se esta moviendo el objeto
    pos += vel * (float)deltaTime;

    if(pos!=lastPos)
    {
        animations[int(currentAnimation)].Update(deltaTime);
        animations[int(currentAnimation)].ApplyToSprite(sprite);
        sprite.setPosition(pos);
    }
    lastPos = pos;

    //----------------------------------------------------------------------------------------------------------
    fireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate)
    {
        bullets.push_back(new Bullet());
        int i = bullets.size() - 1;
        bullets[i]->Initialize(sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width/2.f,sprite.getPosition().y), mousePosition,balaType);
        fireRateTimer = 0;
    }
    /// colision balas enemigo y window
    for (size_t  i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Update(deltaTime);

        if (bullets[i]->GetGlobalBounds().left <= 0.f || bullets[i]->GetGlobalBounds().left >= 1600 ||
                bullets[i]->GetGlobalBounds().top <= 0.f || bullets[i]->GetGlobalBounds().top >= window.getSize().y)
        {
            bullets.erase(bullets.begin() +i);
        }

        for(size_t  j =0; j<enemigos.size(); j++)
        {

            if (Math::DidRectCollide(bullets[i]->GetGlobalBounds(), enemigos[j]->sprite.getGlobalBounds()))
            {
                enemigos[j]->ChangeHealth(damage);
                bullets.erase(bullets.begin() +i);
                break;
            }
        }
    }

     for(size_t  j =0; j<enemigos.size(); j++)
        {
            if(enemigos[j]->dead)
                {
                    enemigos.erase(enemigos.begin()+j);
                }

        }


    ///Colision player contra enemigo
    for(size_t  i =0; i<enemigos.size(); i++)
    {

        if (Math::DidRectCollide(sprite.getGlobalBounds(), enemigos[i]->sprite.getGlobalBounds()))
        {
            ChangeHealth(enemigos[i]->damage);
        }

    }


    if (Math::DidRectCollide(sprite.getGlobalBounds(), botiquin.getSprite().getGlobalBounds()))
    {
        ChangeHealth(100);
        botiquin.sprite.setPosition(sf::Vector2f(-100.f,-100.f));
    }

    if (Math::DidRectCollide(sprite.getGlobalBounds(), pokebolaGolden.getSprite().getGlobalBounds()))
    {
        balaType = "img/pokebolas/pokebolaGolden.png";
        damage = -5;
        pokebolaGolden.sprite.setPosition(sf::Vector2f(-100.f,-100.f));
    }

    ///player window colision

    if(this->sprite.getGlobalBounds().left <= 0.f)
    {
        this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
    }
    //RIGHT
    if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= 1600)
    {
        this->sprite.setPosition(1600 - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
    }
    //TOP
    if(this->sprite.getGlobalBounds().top <= 96.f)
    {
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, 96.f);
    }
    //BOTTOM
    if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= window.getSize().y)
    {
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, window.getSize().y - this->sprite.getGlobalBounds().height);
    }
    ///window colision----------------------------

    //----------------------------------------------------------------------------------------------------------
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (size_t i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Draw(window);
    }

}

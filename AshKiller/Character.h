#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include"Animation.h"

class Character{
private:
    enum class AnimationIndex{
        WalkingUp,
        WalkingDown,
        WalkingLeft,
        WalkingRight,
        Count
    };
private:
    static constexpr float speed = 100.f;
    sf::Vector2f pos;
    sf::Vector2f lastPos {0.0f,0.0f};
    sf::Vector2f vel = {0.0f,0.0f};
    sf::Sprite sprite;
    string pathImg = "img/player.png";
    Animation animations[int(AnimationIndex::Count)];
    AnimationIndex currentAnimation = AnimationIndex::WalkingDown;
public:
    Character(const sf::Vector2f& pos)
        :
        pos(pos)
        {
            sprite.setTextureRect({0,0,64,64});
            animations[int(AnimationIndex::WalkingDown)] = Animation(0,0,64,64,pathImg);
            animations[int(AnimationIndex::WalkingRight)] = Animation(0,128,64,64,pathImg);
            animations[int(AnimationIndex::WalkingLeft)] = Animation(0,64,64,64,pathImg);
            animations[int(AnimationIndex::WalkingUp)] = Animation(0,192,64,64,pathImg);
        }

        void Draw(sf::RenderTarget& rt) const{

            rt.draw(sprite);

        }

        void SetDirection(const sf::Vector2f& dir){

        vel = dir * speed;

        if(dir.x >0.0f){
            currentAnimation = AnimationIndex::WalkingRight;
        }else if(dir.x <0.0f){
            currentAnimation = AnimationIndex::WalkingLeft;
        }else if(dir.y <0.0f){
            currentAnimation = AnimationIndex::WalkingUp;
        }else if(dir.y >0.0f){
            currentAnimation = AnimationIndex::WalkingDown;
        }
        }
        void Update(float dt){

            pos += vel * dt;

            if(pos!=lastPos){
            animations[int(currentAnimation)].Update(dt);
            animations[int(currentAnimation)].ApplyToSprite(sprite);
            sprite.setPosition(pos);
            }
             lastPos = pos;

        }
};



#endif // CHARACTER_H_INCLUDED

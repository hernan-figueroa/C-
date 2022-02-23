#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <string>
#include <iostream>

using namespace std;
class Animation
{
private:
    void Advance()
    {
        if( ++iFrame >= nFrames)
        {
            iFrame = 0;
        }
    }
private:
    int nFrames;
    static constexpr float holdTime = 5.f;
    sf::Texture texture;
    //sf::IntRect frames[nFrames];
    sf::IntRect *frames;
    int iFrame=0;
    float time = 0.0F;

public:
    Animation()=default;
    Animation(int x, int y,int width,int height,string pathImg, int nF)
    {
        nFrames = nF;
        frames = new sf::IntRect[nFrames];
        texture.loadFromFile(pathImg);
        for(int i = 0; i<nFrames; i++)
        {
            frames[i] = {x+i*width,y,width,height};
        }
    }

    void ApplyToSprite(sf::Sprite& s)
    {
        s.setTexture(texture);
        s.setTextureRect(frames[iFrame]);
    }

    void Update(double dt)
    {

        time +=dt;
        while(time>=holdTime)
        {
            time -=holdTime;
            Advance();
        }
    }
};


#endif // ANIMATION_H_INCLUDED

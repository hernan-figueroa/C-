#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include"Animation.h"
#include "Skeleton.h"
#include "Bullet.h"
#include"Element.h"


class Player : public Character
{
private:
    std::vector<Bullet*> bullets;
    float maxFireRate;
    double fireRateTimer;

    sf::Vector2f lastPos= {0.0f,0.0f};
    sf::Vector2f vel = {0.0f,0.0f};

    sf::Text text_nombre;
    sf::Text text_points;

    Animation animations[int(AnimationIndex::Count)];
    AnimationIndex currentAnimation = AnimationIndex::WalkingDown;

public:
    string balaType = "img/pokebolas/pokebola.png";

public:
    Player();
    ~Player();

    void Cargar();
    void Mostrar();
    void CargarNombre();
    void MostrarPuntajes();
    void PuntajeMaximo();

    void Load();
    void SetDirection(const sf::Vector2f& dir);
    void Update(sf::RenderWindow& window,double deltaTime, std::vector<Skeleton*>& enemigos, sf::Vector2f& mousePosition,Element& botiquin,Element&pokebolaGolden);
    void Draw(sf::RenderWindow& window);

    int getPuntaje(){return points;}
    string getNombre(){return nombre;}

};



#endif // PLAYER_H_INCLUDED

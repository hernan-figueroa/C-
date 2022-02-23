#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED
#include <windows.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include"Game.h"


class Enemigo{

protected:
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    int vida;
    int a,b,c,d=96;
    sf::Texture enemy;
    sf::Sprite spriteEnemy;
    std::vector<sf::Sprite>enemies; ///almacena sprites

public:

    void inicializarVariables(){

    this->maxEnemies=2;
    this->enemySpawnTimerMax=5.f;
	this->enemySpawnTimer=this->enemySpawnTimerMax ;

	this->enemy.loadFromFile("img/zombie_n_skeleton2.png");//72,32
    this->spriteEnemy.setTexture(enemy);
    this->spriteEnemy.setTextureRect(sf::IntRect(256,0,32,64));
    this->spriteEnemy.setScale(1.5,1.5);

    }


    void spawnEnemy(sf::RenderTarget& window) /// crea un enemigo en posicion random
{
        this->spriteEnemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window.getSize().x -32)),
		static_cast<float>(rand() % static_cast<int>(window.getSize().y-64 )));
	//Spawn the enemy
	 enemies.push_back(sf::Sprite(spriteEnemy)); /// se usa push_back para agregar una spriteEnemy al vector std::vector<sf::Sprite>enemies;
}

    void update(float playerPosX,float playerPosY,sf::RenderTarget& window){

    /// llama a la funcion spawnEnemy y el timer sirve para que no aparezcan de golpe todos juntos
    float ca=enemySpawnTimer+1.f;
    if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer>=this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy(window);
			this->enemySpawnTimer=0.f ;
		}
		else

			this->enemySpawnTimer=ca;
	}


		for (auto &e : this->enemies)
	{

		sf::Vector2f moveVec;
        moveVec.x=playerPosX - e.getPosition().x;
        moveVec.y=playerPosY - e.getPosition().y;
        float vecLength=sqrt(pow(moveVec.x,2)+ pow(moveVec.y,2));
        moveVec/=vecLength;

        if (moveVec.y > 0){
            if(a<=256){
                e.setTextureRect(sf::IntRect(a,0,32,64));
                e.move(0,1);
                a+=32;
            }else {
                a=96;
            }

        }else if (moveVec.y <0){
            if(b<=256){
                e.setTextureRect(sf::IntRect(b,192,32,64));
                e.move(0,-1);
                b+=32;
            }else {
                b=96;
            }
        }

         if (moveVec.x > 0){

              if(c<=256){
               e.setTextureRect(sf::IntRect(c,128,32,64));
               e.move(1,0);
                c+=32;
            }else {
                c=96;
            }
         }else if (moveVec.x <0){

             if(d<=256){
               e.setTextureRect(sf::IntRect(d,64,32,64));
                e.move(-1,0);
                d+=32;
                std::cout<<d<<"\n";
            }else {
                d=96;
            }
            }

	}


}

void render(sf::RenderTarget& target) /// renderiza los enemigos que contiene  std::vector<sf::Sprite>enemies;
{
	//Rendering all the enemies
	for (auto &e : this->enemies)
	{

		target.draw(e);

	}

}



};

#endif // ENEMIGO_H_INCLUDED

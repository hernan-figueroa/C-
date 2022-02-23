#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include "Fecha.h"
#include "Enemigo.h"
#include <stdio.h>
#include <math.h>

#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game{

private:
    //Variables
    ///window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::Event * evento1;

    //Resources
    sf::Font font;

    //text
    sf::Text uiText;

    //Game logic
    int x;
    int y;
    bool endGame;
    unsigned points;
    int health;
    bool mouseHeld;

    //Game objects
    Enemigo enemigo;

    sf::Texture player;
    sf::Sprite spritePlayer;

    sf::Texture fondo;
    sf::Sprite spriteFondo;

    sf::Texture pasto;
    sf::Sprite spritePasto;

     sf::Texture mira;
    sf::Sprite spriteMira;

    sf::Texture botiquin;
    sf::Sprite spriteBotiquin;

    //Private functions
    void initVariables();
    void initWindows();
    void initFonts();
    void initText();
    void initEnemies();
    void initMira();

public:
    //Constructors / Destructors
    int getPoints(){return points;}
    Game();
    virtual ~Game();


    //Accessors
    const bool running() const;
    const bool getEndGame() const;



    //functions
    void pollEvents();
    void updateText();
    void updateEnemies();
    void updatePlayerPosition();
    void updateMira();
    void updateMousePosition();
    void updateWindowBoundsCollition(const sf::RenderTarget *target);
    void updatePlayer();
    void update();

    void renderPasto(sf::RenderTarget& target);
    void renderFondo(sf::RenderTarget& target);
    void renderPlayer(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void renderMira(sf::RenderTarget& target);
    void renderBotiquin(sf::RenderTarget& target);
    void render();

};



#endif // GAME_H_INCLUDED

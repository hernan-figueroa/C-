#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

    //Mouse positions

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //text
    sf::Text uiText;

    //Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemSpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private functions
    void initVariables();
    void initWindows();
    void initFonts();
    void initText();
    void initEnemies();

public:
    //Constructors / Destructors
    int getPoints(){return points;}
    Game();
    virtual ~Game();


    //Accessors
    const bool running() const;
    const bool getEndGame() const;



    //functions
    void spawnEnemy();
    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

};



#endif // GAME_H_INCLUDED

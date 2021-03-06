#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameState.h"



class Game{

private:
    ///Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<std::string,int> supportedKeys;

    ///Initialization
    void initWindow();
    void initKeys();
    void initStates();


public:
    ///Constructors / Destructors

    Game();
    virtual ~Game();

    ///Functions

    ///Regular

    void endApplication();

    ///update
    void updateDt();
    void updateSMFLEvents();
    void update();

    ///Render
    void render();

    ///Core
    void run();

};



#endif // GAME_H_INCLUDED

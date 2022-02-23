#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "State.h"

class GameState:
        public State
    {
 private:
    Entity player;


   ///Functions
   void initKeybinds();


public:
    GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys);
    virtual ~GameState();


    ///Functions
    void endState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderWindow* target = nullptr) ;

};



#endif // GAMESTATE_H_INCLUDED

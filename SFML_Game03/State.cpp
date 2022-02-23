#include "State.h"

State::State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys){
    this->window = window;
    this->supportedKeys=supportedKeys;
    this->quit = false;
}

State::~State(){

}
const bool& State::getQuit() const{
    return this->quit;
}

void State::checkedForQuit(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

        this->quit = true;
    }
}

void State::update(const float& dt){

}
void State::render(sf::RenderWindow* target){

}


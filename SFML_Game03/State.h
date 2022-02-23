#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "Entiy.h"

class State{

private:

 protected:
     sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string,int> keybinds;
    bool quit;

    ///Resources

    std::vector<sf::Texture> textures;

    ///Functions
    virtual void initKeybinds() =0;

public:
    State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkedForQuit();
    virtual void endState() = 0;

    virtual void updateInput(const float& dt)=0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderWindow* target = nullptr) = 0;

};


#endif // STATE_H_INCLUDED

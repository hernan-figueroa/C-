#include "Game.h"


//Private functions
void Game::initVariables()
{
    this->window == nullptr;

    //Game logic
    this->endGame=false;
    this->points = 0;
    this->health=10;

    this->fondo.loadFromFile("img/fondo.png");
    this->spriteFondo.setTexture(fondo);


    this->pasto.loadFromFile("img/piso3d.png");
    this->spritePasto.setTexture(pasto);
    this->spritePasto.setScale(sf::Vector2f(0.5,0.5));

    this->player.loadFromFile("img/player.png");
    this->spritePlayer.setTexture(player);
    this->spritePlayer.setPosition(0.f,400.f);
    this->spritePlayer.setScale(sf::Vector2f(1,1));
    this->spritePlayer.setTextureRect(sf::IntRect(0,0,64,64));

    //mira.SpriteMira();

    this->mira.loadFromFile("img/mira2.png");
    this->spriteMira.setTexture(mira);
    this->spriteMira.setPosition(200.f,200.f);
    this->spriteMira.setTextureRect(sf::IntRect(0,0,564,516));
    this->spriteMira.setScale(sf::Vector2f(0.1,0.1));

    this->botiquin.loadFromFile("img/botiquin2.png");
    this->spriteBotiquin.setTexture(botiquin);
    this->spriteBotiquin.setPosition(250.f,250.f);
    this->spriteBotiquin.setTextureRect(sf::IntRect(0,0,300,300));
    this->spriteBotiquin.setScale(sf::Vector2f(0.2,0.2));
    x=0;
}

void Game::initWindows()
{
    this->videoMode.height=600;
    this->videoMode.width=800;

    this->window = new sf::RenderWindow(this->videoMode,"Game 1",sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(30);


}

void Game::initFonts()
{

    if(!this->font.loadFromFile("font/Homer_Simpson.ttf"))
    {

        std::cout<<"ERROR::GAME::INITFONTS::Failed to load font!"<<"\n";
    }

}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");


}
void Game::initEnemies() /// inicializa las variables del enemigo
{
   enemigo.inicializarVariables();
}

//Constructors / Destructors

Game::Game()
{

    this->initVariables();
    this->initWindows();
    this->initFonts();
    this->initText();
    this->initEnemies();

    window->setMouseCursorVisible(false);

    evento1 = new sf::Event;
}

Game::~Game()
{

    delete this->window;

}

//Accessors
const bool Game::running() const
{

    return this->window->isOpen();
}

//Functions
const bool Game::getEndGame() const
{

    return this->endGame;

}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->ev.key.code==sf::Keyboard::Escape)
                this-> window->close();
            break;
        }
        while(this->window->pollEvent(*evento1)){
            switch(this->evento1->type){
                case sf::Event::MouseMoved:
                    this->spriteMira.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
                    //exit(1);
                    break;
            }
        }
    }
}
void Game::updateEnemies(){ /// llama a la funcion spawnEnemy y el timer sirve para que no aparezcan de golpe todos juntos

    enemigo.update(this->spritePlayer.getPosition().x , this->spritePlayer.getPosition().y,*this->window);

}

void Game::updateWindowBoundsCollition(const sf::RenderTarget *target){
    //LEFT
    if(this->spritePlayer.getGlobalBounds().left <= 0.f){
        this->spritePlayer.setPosition(0.f, this->spritePlayer.getGlobalBounds().top);
    }
    //RIGHT
    if(this->spritePlayer.getGlobalBounds().left + this->spritePlayer.getGlobalBounds().width >= target->getSize().x){
        this->spritePlayer.setPosition(target->getSize().x - this->spritePlayer.getGlobalBounds().width, this->spritePlayer.getGlobalBounds().top);
    }
    //TOP
    if(this->spritePlayer.getGlobalBounds().top <= 0.f){
        this->spritePlayer.setPosition(this->spritePlayer.getGlobalBounds().left, 0.f);
    }
    //BOTTOM
    if(this->spritePlayer.getGlobalBounds().top + this->spritePlayer.getGlobalBounds().height >= target->getSize().y){
        this->spritePlayer.setPosition(this->spritePlayer.getGlobalBounds().left, target->getSize().y - this->spritePlayer.getGlobalBounds().height);
    }
}

void Game::updatePlayerPosition(){
   // if(this->spritePlayer.getGlobalBounds().intersects(this->window.get))
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
             if(x<256){
               this->spritePlayer.setTextureRect(sf::IntRect(x,128,64,64));
                spritePlayer.move(sf::Vector2f(2.f,0.f));
             if(x<192){
                x+=64;
             }else x=0;

        }
     }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
             if(x<256){
               this->spritePlayer.setTextureRect(sf::IntRect(x,64,64,64));
                spritePlayer.move(sf::Vector2f(-2.f,0.f));
             if(x<192){
                    x+=64;
             }else x=0;
            }
    }
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            if(x<256){
                this->spritePlayer.setTextureRect(sf::IntRect(x,0,64,64));
                spritePlayer.move(sf::Vector2f(0.f,2.f));
                if(x<192){
                    x+=64;
                }else x=0;
            }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

            if(x<=256){
                this->spritePlayer.setTextureRect(sf::IntRect(x,192,64,64));
                spritePlayer.move(sf::Vector2f(0.f,-2.f));
            if(x<192){
                x+=64;
            }else x=0;

            }
    }
}


void Game::updateText()
{

    std::stringstream ss;
    ss<<"Points: "<< this->points<<"\n"<< "Health: "<<this->health<<"\n";
    this->uiText.setString(ss.str());
}


void Game::updatePlayer(){
    this->updateWindowBoundsCollition(this->window);
}


void Game::update()
{

    this ->pollEvents();

    if(this->endGame== false)
    {

        this->updateEnemies();
        this->updatePlayerPosition();
        this->updateText();

    }

    if(this->health<=0)
    {
        this->endGame=true;
    }

    //update mouse position
    //relative to the screen
    //std::cout <<"Mouse pos: "<<sf::Mouse::getPosition().x<<" "<<sf::Mouse::getPosition().y <<"\n";
    //relative to the window
    // std::cout <<"Mouse pos: "<<sf::Mouse::getPosition(*this->window).x<<" "<<sf::Mouse::getPosition(*this->window).y <<"\n";
}

void Game::renderText(sf::RenderTarget& target)
{

    target.draw(this->uiText);

}

void Game::renderEnemies(sf::RenderTarget& target) /// renderiza los enemigos que contiene  std::vector<sf::Sprite>enemies;
{
	//Rendering all the enemies
	enemigo.render(target);
}

void Game::renderFondo(sf::RenderTarget& target)
{      float xPos=0;
        float yPos =0;

        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){

            spriteFondo.setPosition(xPos,yPos);
            this->spriteFondo.setTextureRect(sf::IntRect(0,385,320,125));
            target.draw(spriteFondo);
            yPos+=125;

            }
            yPos =0;
            xPos+=320;
            spriteFondo.setPosition(xPos,yPos);
            this->spriteFondo.setTextureRect(sf::IntRect(0,385,320,125));
            target.draw(spriteFondo);
        }
}

void Game::renderPasto(sf::RenderTarget& target){
        int b=0;
        for(int i=0;i<20;i++){

            spritePasto.setPosition(b,490);
            this->spritePasto.setTextureRect(sf::IntRect(415,390,103,195));
            target.draw(spritePasto);
            b+=50;
        }



        int a=0;
        for(int i=0;i<20;i++){

            spritePasto.setPosition(a,540);
            this->spritePasto.setTextureRect(sf::IntRect(720,203,103,195));
            target.draw(spritePasto);
            a+=50;
        }

        for(int i=0;i<8;i++){
        spritePasto.setPosition(i*103,500);
        this->spritePasto.setTextureRect(sf::IntRect(205,700,103,205));
         target.draw(spritePasto);
        }

}

void Game::renderPlayer(sf::RenderTarget& target)
{
        target.draw(spritePlayer);

}

void Game::renderMira(sf::RenderTarget& target){

    target.draw(this->spriteMira);
}

void Game::renderBotiquin(sf::RenderTarget& target){

    target.draw(this->spriteBotiquin);
}
void Game::render()
{

    this->window->clear();

    //Draw game objects
    this->renderFondo(*this->window);
    this->renderPasto(*this->window);
     this->renderBotiquin(*this->window);
    ///mira.renderMira(*this->window);
    this->renderEnemies(*this->window);
    this->renderMira(*this->window);
    this->renderPlayer(*this->window);


    this->renderText(*this->window);

    this->window->display();
}

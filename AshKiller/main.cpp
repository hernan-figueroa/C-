#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include<cstring>
#include <windows.h>

#include "Player.h"
#include "Skeleton.h"
#include "TileMap.h"
#include "Element.h"
#include "Math.h"
#include "Menu.h"
#include "Textbox.h"
#include "RegistroPuntaje.h"
#include "funcionesPuntaje.h"

bool comp ( RegistroPuntaje& a,  RegistroPuntaje& b)
{
    return  a.getPoints() > b.getPoints();
}

int main()
{
    std::srand(static_cast<unsigned>(time(NULL))); /// random
    sf::View view(sf::FloatRect(800, 600, 1600, 600));

    ///-------------------------------- INITIALIZE --------------------------------
    sf::RenderWindow window(sf::VideoMode(800, 600), "ASH killer", sf::Style::Default);
    window.setFramerateLimit(30);
    Menu menu(window.getSize().x,window.getSize().y);

    sf::Texture menuTexture;
    sf::Texture menuTextureName;
    sf::Texture menuTexturePuntaje;

    if(!menuTexture.loadFromFile("img/ASH KILLER3.png"))
        std::cout<<"ERROR"<<std::endl;
    if(!menuTextureName.loadFromFile("img/ASH KILLER NAME.png"))
        std::cout<<"ERROR"<<std::endl;
    if(!menuTexturePuntaje.loadFromFile("img/ASH KILLER PUNTAJES.png"))
        std::cout<<"ERROR"<<std::endl;

    sf::Sprite spriteMenu;
    sf::Sprite spriteMenuName;
    sf::Sprite spritePuntajes;

    spriteMenu.setTexture(menuTexture);
    spriteMenuName.setTexture(menuTextureName);
    spritePuntajes.setTexture(menuTexturePuntaje);

    sf::Texture mira;
    sf::Sprite spriteMira;

    mira.loadFromFile("img/mira2.png");

    spriteMira.setTexture(mira);
    spriteMira.setScale(0.08f,0.08f);

    sf::Text mostrarPuntajes[3];
    sf::Text mostrarPuntos[3];

    ///-------------------------------- INITIALIZE --------------------------------
    while(window.isOpen())
    {
        window.setMouseCursorVisible(false);
        sf::Vector2f inicio(0.f,0.f);
        sf::Vector2f salida(1600-64,32*3);
        Element botiquin("img/botiquin2.png",300,300,0.15,0.15);
        Element pokebolaGolden("img/pokebolas/pokebolaGolden.png",95,123,0.25,0.25);
        Element exitLevel("img/doorOpen0.png",32,32,2,2,salida);
        bool doorIsOpen = false;
        Player player;

        sf::Font textBoxFont;
        textBoxFont.loadFromFile("font/Homer_Simpson.ttf");
        Textbox textbox1(50, sf::Color::White, true);
        textbox1.setFont(textBoxFont);
        textbox1.setPosition({90, 150});

        std::vector<Skeleton*> enemigos;

//text
        sf::Font font;

        sf::Text uiText;

        ///-------------------------------- GameOver --------------------------------

        bool Menu=true;

        ///------------------------------Map-----------------------

        TileMap map;
        sf::Vector2f positionView(window.getSize().x/2,window.getSize().y/2);
        view.reset(sf::FloatRect(0,0,800,600));
        view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
        ///------------------------------Map-----------------------

        ///-------------------------------- INITIALIZE --------------------------------

        if(!font.loadFromFile("font/Homer_Simpson.ttf"))
            std::cout<<"ERROR::GAME::INITFONTS::Failed to load font!"<<"\n";
        uiText.setFont(font);
        uiText.setCharacterSize(24);
        uiText.setFillColor(sf::Color::White);
        uiText.setString("NONE");
        ///-------------------------------- INITIALIZE --------------------------------

        ///-------------------------------- LOAD --------------------------------
        player.Load();
        ///-------------------------------- LOAD --------------------------------
        sf::Clock clock;
        int a=0;
        int b=0;
        int num=1; // tipos de enemigos
        int level = 1;
        sf::Event event;
        ///-------------------------------- UPDATE --------------------------------
        while(Menu)
        {
            bool GameOver=false;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        menu.MoverArriba();
                        break;
                    }
                    if(event.key.code == sf::Keyboard::Down)
                    {
                        menu.MoverAbajo();
                        break;
                    }
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        int x = menu.itemSeleccionado();
                        if(x == 0)
                        {
///-------------------------JUEGO-------------------------------------
                            sf::Event eventGame;
                            while (!GameOver)
                            {
                                if(player.health<=0)
                                {
                                    Math::PositionView(window,positionView,  inicio);
                                    view.setCenter(positionView);
                                    window.setView(view);
                                    while (window.pollEvent(eventGame))
                                    {
                                        if(eventGame.type == sf::Event::TextEntered)
                                        {
                                            textbox1.typedOn(eventGame);
                                        }
                                        if(eventGame.key.code == sf::Keyboard::Tab)
                                        {
                                            RegistroPuntaje jugador;
                                            string tmp_string = textbox1.getText();
                                            auto c_string = tmp_string.c_str();

                                            jugador.setNombre(c_string);
                                            jugador.setPoints(player.points);
                                            std::cout<<textbox1.getText()<<"\n";
                                            jugador.grabarEnDisco();
                                            std::cout<<jugador.getNombre()<<"-----------"<<"\n";
                                            GameOver=true;
                                            Menu=false;
                                            break;
                                        }
                                    }
                                    window.clear();
                                    window.draw(spriteMenuName);
                                    textbox1.drawTo(window);
                                    window.display();
                                }
                                ///------------------------Mientras este con vida ------------------------
                                while(player.health>0)
                                {
                                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                    {
                                        player.health=0;
                                        GameOver=true;
                                        Menu=false;
                                    }

                                    sf::Event event;
                                    while (window.pollEvent(event))
                                    {
                                        if (event.type == sf::Event::Closed)
                                            window.close();
                                    }

                                    ///-------------------------------- UPDATE --------------------------------

                                    sf::Time deltaTimeTimer = clock.restart();
                                    double deltaTime = deltaTimeTimer.asMicroseconds()/10000.0;

                                    if(a<10)
                                    {
                                        enemigos.push_back(new Skeleton((rand() % num)+1));
                                        enemigos[enemigos.size()-1]->Load();
                                        a++;
                                    }
                                    if(enemigos.size()<10 && a==10)
                                    {
                                        a-=1;
                                        b++;
                                        if(b>20)
                                        {
                                            a=15;
                                        }
                                    }
                                    //Posicion del mouse convertido por el uso de la clase View
                                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                                    sf::Vector2f mousePosition = worldPos;

                                    spriteMira.setPosition((mousePosition.x - spriteMira.getGlobalBounds().width/2)+10,
                                                           (mousePosition.y - spriteMira.getGlobalBounds().height/2)+10);
                                    //--------------------------------------------------------------------

                                    for(size_t i =0; i<enemigos.size(); i++)
                                    {
                                        enemigos[i]->Update(deltaTime,player.pos,player.points);
                                    }

                                    player.Update(window,deltaTime, enemigos, mousePosition,botiquin,pokebolaGolden);
                                    std::stringstream ss;
                                    ss<<"Points: "<< player.points<<"\n"<< "Health: "<<(int)player.health<<"\n";
                                    uiText.setString(ss.str());
                                    uiText.setPosition(view.getCenter().x-399,view.getCenter().y-300);

                                    if(enemigos.size() ==0 && level!=3)
                                    {
                                        doorIsOpen=true;
                                        if(Math::DidRectCollide(player.sprite.getGlobalBounds(),exitLevel.sprite.getGlobalBounds()))
                                        {
                                            level++;
                                            if(level==2)
                                            {
                                                map.initialaze("Map2.txt");
                                                num=2;
                                                doorIsOpen=false;
                                                exitLevel.setTexture("img/exit2.png");
                                                salida.y+=48;
                                                exitLevel.sprite.setPosition(salida);
                                            }
                                            else
                                            {
                                                map.initialaze("Map3.txt");
                                                num=3;
                                            }
                                            player.pos = sf::Vector2f(50,450);
                                            a=0;
                                            b=0;

                                        }
                                    }

                                    if(level==3)
                                    {
                                        b=0;
                                    }

                                    //----------VIEW POSITION--------------
                                    if(GameOver)
                                    {
                                        Math::PositionView(window,positionView,inicio);
                                    }
                                    else
                                    {
                                        Math::PositionView(window,positionView,player.pos);
                                    }


                                    view.setCenter(positionView);
                                    //----------VIEW POSITION--------------

                                    ///-------------------------------- UPDATE --------------------------------

                                    ///-------------------------------- DRAW --------------------------------
                                    window.clear();

                                    map.draw(window);
                                    if(doorIsOpen && level!=3)
                                    {
                                        exitLevel.Draw(window);
                                    }


                                    window.setView(view);

                                    botiquin.Draw(window);
                                    pokebolaGolden.Draw(window);

                                    for(size_t i =0; i<enemigos.size(); i++)
                                    {
                                        enemigos[i]->Draw(window);
                                    }


                                    player.Draw(window);
                                    window.draw(uiText);
                                    window.draw(spriteMira);
                                    window.display();
                                    ///-------------------------------- DRAW --------------------------------
                                }
                                ///------------------------Mientras este con vida ------------------------

                            }

                        }
                        if(x == 1)
                        {
                            if(window.isOpen())
                            {
                                sf::Event aevent;
                                while(window.pollEvent(aevent))
                                {
                                    if(aevent.type == sf::Event::Closed)
                                    {
                                        window.close();
                                    }
                                }

                                std::vector<RegistroPuntaje> registros;

                                RegistroPuntaje obj;
                                int pos =0;
                                while(obj.leerDeDisco(pos))
                                {
                                    registros.push_back(obj);
                                    pos++;
                                }

                                std::sort(registros.begin(),registros.end(),&comp);

                                string p1, p2, p3;

                                if(registros.size()<3)
                                {
                                    for(int i = 0; i < registros.size(); i++)
                                    {
                                        std::cout<<registros[i].getNombre()<<" : "<<registros[i].getPoints()<<"\n";

                                        mostrarPuntajes[0].setFont(font);
                                        mostrarPuntajes[0].setCharacterSize(40);
                                        mostrarPuntajes[0].setColor(sf::Color::Yellow);
                                        mostrarPuntajes[0].setString(registros[0].getNombre());
                                        mostrarPuntajes[0].setOrigin(mostrarPuntajes[0].getLocalBounds().width/2, mostrarPuntajes[0].getLocalBounds().height/2);
                                        mostrarPuntajes[0].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2 + 105));

                                        mostrarPuntos[0].setFont(font);
                                        mostrarPuntos[0].setCharacterSize(40);
                                        mostrarPuntos[0].setColor(sf::Color::Yellow);
                                        mostrarPuntos[0].setString(to_string(registros[0].getPoints()));
                                        mostrarPuntos[0].setOrigin(mostrarPuntos[0].getLocalBounds().width/2, mostrarPuntos[0].getLocalBounds().height/2);
                                        mostrarPuntos[0].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2+80));

                                        mostrarPuntajes[1].setFont(font);
                                        mostrarPuntajes[1].setCharacterSize(40);
                                        mostrarPuntajes[1].setColor(sf::Color::White);
                                        mostrarPuntajes[1].setString(registros[1].getNombre());
                                        mostrarPuntajes[1].setOrigin(mostrarPuntos[1].getLocalBounds().width/2, mostrarPuntos[1].getLocalBounds().height/2);
                                        mostrarPuntajes[1].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2-40));

                                        mostrarPuntos[1].setFont(font);
                                        mostrarPuntos[1].setCharacterSize(40);
                                        mostrarPuntos[1].setColor(sf::Color::White);
                                        mostrarPuntos[1].setString(to_string(registros[1].getPoints()));
                                        mostrarPuntos[1].setOrigin(mostrarPuntos[1].getLocalBounds().width/2, mostrarPuntos[1].getLocalBounds().height/2);
                                        mostrarPuntos[1].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2-15));

                                        mostrarPuntajes[2].setFont(font);
                                        mostrarPuntajes[2].setCharacterSize(40);
                                        mostrarPuntajes[2].setColor(sf::Color::White);
                                        mostrarPuntajes[2].setString(registros[2].getNombre());
                                        mostrarPuntajes[2].setOrigin(mostrarPuntos[2].getLocalBounds().width/2, mostrarPuntos[2].getLocalBounds().height/2);
                                        mostrarPuntajes[2].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2+25));

                                        mostrarPuntos[2].setFont(font);
                                        mostrarPuntos[2].setCharacterSize(40);
                                        mostrarPuntos[2].setColor(sf::Color::White);
                                        mostrarPuntos[2].setString(to_string(registros[2].getPoints()));
                                        mostrarPuntos[2].setOrigin(mostrarPuntos[2].getLocalBounds().width/2, mostrarPuntos[2].getLocalBounds().height/2);
                                        mostrarPuntos[2].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2+50));
                                    }
                                }
                                else
                                {
                                    for(int i = 0; i < 3; i++)
                                    {
                                        std::cout<<registros[i].getNombre()<<" : "<<registros[i].getPoints()<<"\n";

                                        mostrarPuntajes[0].setFont(font);
                                        mostrarPuntajes[0].setCharacterSize(40);
                                        mostrarPuntajes[0].setColor(sf::Color::Yellow);
                                        mostrarPuntajes[0].setString(registros[0].getNombre());
                                        mostrarPuntajes[0].setOrigin(mostrarPuntajes[0].getLocalBounds().width/2, mostrarPuntajes[0].getLocalBounds().height/2);
                                        mostrarPuntajes[0].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2 - 105));

                                        mostrarPuntos[0].setFont(font);
                                        mostrarPuntos[0].setCharacterSize(40);
                                        mostrarPuntos[0].setColor(sf::Color::Yellow);
                                        mostrarPuntos[0].setString(to_string(registros[0].getPoints()));
                                        mostrarPuntos[0].setOrigin(mostrarPuntos[0].getLocalBounds().width/2, mostrarPuntos[0].getLocalBounds().height/2);
                                        mostrarPuntos[0].setPosition(sf::Vector2f(window.getSize().x/5 , window.getSize().y/2 -80));

                                        mostrarPuntajes[1].setFont(font);
                                        mostrarPuntajes[1].setCharacterSize(40);
                                        mostrarPuntajes[1].setColor(sf::Color::White);
                                        mostrarPuntajes[1].setString(registros[1].getNombre());
                                        mostrarPuntajes[1].setOrigin(mostrarPuntajes[1].getLocalBounds().width/2, mostrarPuntajes[1].getLocalBounds().height/2);
                                        mostrarPuntajes[1].setPosition(sf::Vector2f(window.getSize().x/5 , window.getSize().y/2 - 40));

                                        mostrarPuntos[1].setFont(font);
                                        mostrarPuntos[1].setCharacterSize(40);
                                        mostrarPuntos[1].setColor(sf::Color::White);
                                        mostrarPuntos[1].setString(to_string(registros[1].getPoints()));
                                        mostrarPuntos[1].setOrigin(mostrarPuntos[1].getLocalBounds().width/2, mostrarPuntos[1].getLocalBounds().height/2);
                                        mostrarPuntos[1].setPosition(sf::Vector2f(window.getSize().x/5 , window.getSize().y/2- 15));

                                        mostrarPuntajes[2].setFont(font);
                                        mostrarPuntajes[2].setCharacterSize(40);
                                        mostrarPuntajes[2].setColor(sf::Color::White);
                                        mostrarPuntajes[2].setString(registros[2].getNombre());
                                        mostrarPuntajes[2].setOrigin(mostrarPuntajes[2].getLocalBounds().width/2, mostrarPuntajes[2].getLocalBounds().height/2);
                                        mostrarPuntajes[2].setPosition(sf::Vector2f(window.getSize().x/5 , window.getSize().y/2 +25));

                                        mostrarPuntos[2].setFont(font);
                                        mostrarPuntos[2].setCharacterSize(40);
                                        mostrarPuntos[2].setColor(sf::Color::White);
                                        mostrarPuntos[2].setString(to_string(registros[2].getPoints()));
                                        mostrarPuntos[2].setOrigin(mostrarPuntos[2].getLocalBounds().width/2, mostrarPuntos[2].getLocalBounds().height/2);
                                        mostrarPuntos[2].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/2+50));
                                    }
                                }

                                while(Menu)
                                {
                                    while(window.pollEvent(aevent))
                                    {
                                        if(aevent.type == sf::Event::KeyPressed)
                                        {
                                            if(aevent.key.code == sf::Keyboard::Escape)
                                            {
                                                Menu = false;
                                            }
                                        }
                                    }
                                    window.clear();
                                    window.draw(spritePuntajes);
                                    if(registros.size() == 1)
                                    {
                                        window.draw(mostrarPuntajes[0]);
                                        window.draw(mostrarPuntos[0]);
                                    }
                                    else if(registros.size() == 2)
                                    {
                                        window.draw(mostrarPuntajes[0]);
                                        window.draw(mostrarPuntos[0]);
                                        window.draw(mostrarPuntajes[1]);
                                        window.draw(mostrarPuntos[1]);
                                    }
                                    else
                                    {
                                        window.draw(mostrarPuntajes[0]);
                                        window.draw(mostrarPuntos[0]);
                                        window.draw(mostrarPuntajes[1]);
                                        window.draw(mostrarPuntos[1]);
                                        window.draw(mostrarPuntajes[2]);
                                        window.draw(mostrarPuntos[2]);
                                    }
                                    window.display();
                                }
                            }
                        }
                        if(x == 2)
                        {
                            window.close();
                            break;
                        }
                    }
                }
            }
            window.clear();
            window.draw(spriteMenu);
            menu.draw(window);
            window.display();
        }
    }
    return 0;
}

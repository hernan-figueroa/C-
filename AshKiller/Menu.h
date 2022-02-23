#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NUMERO_MAXIMO_DE_ITEMS 3

class Menu{
private:
    int seleccionarItemIndex;
    sf::Font fuente;
    sf::Text menu[NUMERO_MAXIMO_DE_ITEMS];

public:
    Menu(float ancho, float alto){
        if(!fuente.loadFromFile("font/BBBInvader-Regular.otf")){
                std::cout<<"ERROR"<<std::endl;


        }

        menu[0].setFont(fuente);
        menu[0].setCharacterSize(20);
        menu[0].setColor(sf::Color::White);
        menu[0].setString("Jugar");
        menu[0].setOrigin(menu[0].getLocalBounds().width/2, menu[0].getLocalBounds().height/2);
        menu[0].setPosition(sf::Vector2f(ancho/5, alto/(NUMERO_MAXIMO_DE_ITEMS+1)*1));

        menu[1].setFont(fuente);
        menu[1].setCharacterSize(20);
        menu[1].setColor(sf::Color::White);
        menu[1].setString("Puntuacion maxima");
        menu[1].setOrigin(menu[1].getLocalBounds().width/2, menu[1].getLocalBounds().height/2);
        menu[1].setPosition(sf::Vector2f(ancho/5, alto/(NUMERO_MAXIMO_DE_ITEMS+1)*2));

        menu[2].setFont(fuente);
        menu[2].setCharacterSize(20);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("Salir del juego");
        menu[2].setOrigin(menu[2].getLocalBounds().width/2, menu[2].getLocalBounds().height/2);
        menu[2].setPosition(sf::Vector2f(ancho/5, alto/(NUMERO_MAXIMO_DE_ITEMS+1)*3));

        seleccionarItemIndex = -1;
    }
    ~Menu(){}

    void draw(sf::RenderWindow& window){
        for(int i=0;i<NUMERO_MAXIMO_DE_ITEMS;i++){
            window.draw(menu[i]);
        }
    }
    void MoverArriba(){
        if(seleccionarItemIndex - 1 >= 0){
            menu[seleccionarItemIndex].setFillColor(sf::Color::White);

            seleccionarItemIndex--;
            if(seleccionarItemIndex == -1){
                seleccionarItemIndex = 3;
            }
            menu[seleccionarItemIndex].setFillColor(sf::Color::Yellow);
        }
    }
    void MoverAbajo(){
        if(seleccionarItemIndex + 1 <= NUMERO_MAXIMO_DE_ITEMS){
            menu[seleccionarItemIndex].setFillColor(sf::Color::White);
            seleccionarItemIndex++;
            if(seleccionarItemIndex == 3){
                seleccionarItemIndex = 0;
            }
            menu[seleccionarItemIndex].setFillColor(sf::Color::Yellow);
        }
    }

    int itemSeleccionado(){return seleccionarItemIndex;}
};

#endif // MENU_H_INCLUDED

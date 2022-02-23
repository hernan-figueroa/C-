#ifndef FUNCIONESPUNTAJE_H_INCLUDED
#define FUNCIONESPUNTAJE_H_INCLUDED

void mostrarPuntaje(sf::Text *mostrarPuntajes, sf::Text *mostrarPuntos, std::vector<RegistroPuntaje> registros, sf::Font font, sf::RenderWindow &window)
{
    mostrarPuntajes[0].setFont(font);
    mostrarPuntajes[0].setCharacterSize(40);
    mostrarPuntajes[0].setColor(sf::Color::Yellow);
    mostrarPuntajes[0].setString(registros[0].getNombre());
    mostrarPuntajes[0].setOrigin(mostrarPuntajes[0].getLocalBounds().width/2, mostrarPuntajes[0].getLocalBounds().height/2);
    mostrarPuntajes[0].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*1));

    mostrarPuntos[0].setFont(font);
    mostrarPuntos[0].setCharacterSize(40);
    mostrarPuntos[0].setColor(sf::Color::Yellow);
    mostrarPuntos[0].setString(to_string(registros[0].getPoints()));
    mostrarPuntos[0].setOrigin(mostrarPuntos[0].getLocalBounds().width/2, mostrarPuntos[0].getLocalBounds().height/2);
    mostrarPuntos[0].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*1.2));


    mostrarPuntajes[1].setFont(font);
    mostrarPuntajes[1].setCharacterSize(40);
    mostrarPuntajes[1].setColor(sf::Color::White);
    mostrarPuntajes[1].setString(registros[1].getNombre());
    mostrarPuntajes[1].setOrigin(mostrarPuntos[1].getLocalBounds().width/2, mostrarPuntos[1].getLocalBounds().height/2);
    mostrarPuntajes[1].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*2));


    mostrarPuntos[1].setFont(font);
    mostrarPuntos[1].setCharacterSize(40);
    mostrarPuntos[1].setColor(sf::Color::White);
    mostrarPuntos[1].setString(to_string(registros[1].getPoints()));
    mostrarPuntos[1].setOrigin(mostrarPuntos[1].getLocalBounds().width/2, mostrarPuntos[1].getLocalBounds().height/2);
    mostrarPuntos[1].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*2.2));

    mostrarPuntajes[2].setFont(font);
    mostrarPuntajes[2].setCharacterSize(40);
    mostrarPuntajes[2].setColor(sf::Color::White);
    mostrarPuntajes[2].setString(registros[2].getNombre());
    mostrarPuntajes[2].setOrigin(mostrarPuntos[2].getLocalBounds().width/2, mostrarPuntos[2].getLocalBounds().height/2);
    mostrarPuntajes[2].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*3));

    mostrarPuntos[2].setFont(font);
    mostrarPuntos[2].setCharacterSize(40);
    mostrarPuntos[2].setColor(sf::Color::White);
    mostrarPuntos[2].setString(to_string(registros[2].getPoints()));
    mostrarPuntos[2].setOrigin(mostrarPuntos[2].getLocalBounds().width/2, mostrarPuntos[2].getLocalBounds().height/2);
    mostrarPuntos[2].setPosition(sf::Vector2f(window.getSize().x/5, window.getSize().y/(3+1)*3.2));

}

void displayPuntajes(sf::Text *mostrarPuntajes, sf::Text *mostrarPuntos, sf::RenderWindow &window){
    window.clear();
    window.draw(mostrarPuntajes[0]);
    window.draw(mostrarPuntos[0]);
    window.draw(mostrarPuntajes[1]);
    window.draw(mostrarPuntos[1]);
    window.draw(mostrarPuntajes[2]);
    window.draw(mostrarPuntos[2]);
    window.display();
}

#endif // FUNCIONESPUNTAJE_H_INCLUDED

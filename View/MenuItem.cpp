#include "MenuItem.h"
#include "fmt/core.h"
#include <string>


MenuItem::MenuItem(std::string itemText, float positionX, float positionY)
    : itemText(itemText),positionX(positionX), positionY(positionY){

}

MenuItem::~MenuItem() {}

auto MenuItem::createMenuItem(sf::RenderWindow &window, int winSizeX, int winSizeY) -> sf::Sprite{
    renderTexture.create(winSizeX, winSizeY);

    if(!font.loadFromFile("../font/arial.ttf")){
        fmt::println("{}","Nie można załadować czcionki") ;
    }

    font.loadFromFile("../font/arial.ttf");

    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setPosition(sf::Vector2f(positionX/2, positionY * 1)); //width/2
    rectangle.setFillColor(sf::Color::Magenta);

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString(itemText);
    text.setPosition(rectangle.getPosition().x + 20, rectangle.getPosition().y + 5);

    renderTexture.draw(rectangle);
    renderTexture.draw(text);

    renderTexture.display();
    sprite.setTexture(renderTexture.getTexture());

    return sprite;
}
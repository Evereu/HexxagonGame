#include <SFML/Graphics.hpp>
#include "Logic/Move.h"
#include "View/ScoreView.h"
#include "View/Menu.h"

int main() {
    //https://en.sfml-dev.org/forums/index.php?topic=10351.0
    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon", sf::Style::Titlebar | sf::Style::Close);
    auto event = sf::Event();

   // Move move;
    //RenderMap renderMap;
    //auto map = renderMap.renderHexagonMap();
    //GameState gameState;


    Menu menu;
    MenuState menuState;


    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                auto position = sf::Mouse::getPosition(window);

                auto mousePositionWindow = window.mapPixelToCoords(position);

                //move.draw(window,mousePositionWindow, map, gameState);

                menuState = menu.draw(window,mousePositionWindow, menuState);
                window.display();
            }
        }
    }
}
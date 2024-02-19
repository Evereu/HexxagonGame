#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "Move.h"
#include "../View/RenderMap.h"
#include "../View/ScoreView.h"

auto Game::runGame(sf::RenderWindow &window) -> void {

    Move move;

    RenderMap renderMap;

    GameState gameState;

    auto map = renderMap.renderHexagonMap();

    auto event = sf::Event();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto position = sf::Mouse::getPosition(window);
                auto mousePositionWindow = window.mapPixelToCoords(position);

                move.draw(window, mousePositionWindow, map, gameState);

                window.display();
            }
        }
    }
}

auto Game::runScore(sf::RenderWindow &window) -> void {

    ScoreView scoreView;

    auto event = sf::Event();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear();
            scoreView.drawScore(window);
            window.display();
        }
    }
}
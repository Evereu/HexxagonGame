#include "Menu.h"
#include "MenuItem.h"
#include "../Logic/Move.h"
#include "RenderMap.h"
#include "ScoreView.h"
#include "../Logic/Game.h"

Menu::Menu() {}

Menu::~Menu() {}

auto Menu::draw( sf::RenderWindow &window, sf::Vector2<float> &mousePosition, MenuState &menuState) -> MenuState {

    GameState currentPlayer;
    RenderMap renderMap;
    Move move;
    ScoreView scoreView;
    Game game;

    auto map = renderMap.renderHexagonMap();


    sf::Texture background;
    if (!background.loadFromFile("../Background/background.jpg")) {
    }
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / background.getSize().x,
                              static_cast<float>(window.getSize().y) / background.getSize().y);

    window.draw(backgroundSprite);


    auto winSizeX = window.getSize().x;
    auto winSizeY = window.getSize().y;
    auto menuVector = std::vector<sf::Sprite>();

    MenuItem menuItemLocal("Graj lokalnie",400, 300);
    MenuItem menuItemAi("Graj z komputerem",400, 400);
    MenuItem menuItemScores("Wyniki",400, 500);
    MenuItem menuItemExit("Wyjscie",400, 600);

    auto menuLocal= menuItemLocal.createMenuItem(window, winSizeX,winSizeY);
    auto menuAi = menuItemAi.createMenuItem(window,winSizeX,winSizeY);
    auto menuScore = menuItemScores.createMenuItem(window,winSizeX,winSizeY);
    auto menuExit = menuItemExit.createMenuItem(window,winSizeX,winSizeY);

    window.draw(menuLocal);
    window.draw(menuAi);
    window.draw(menuScore);
    window.draw(menuExit);


            if (menuItemLocal.rectangle.getGlobalBounds().contains(mousePosition)) {

                menuState = MenuState::MenuItemLocal;

                }  else if (menuItemAi.rectangle.getGlobalBounds().contains(mousePosition)) {

                menuState = MenuState::MenuItemAi;


                }  else if (menuItemScores.rectangle.getGlobalBounds().contains(mousePosition)) {

                menuState = MenuState::MenuItemScores;


                }  else if (menuItemExit.rectangle.getGlobalBounds().contains(mousePosition)) {

                menuState = MenuState::MenuItemExit;
                }


    switch (menuState) {

        case MenuState::CurMenu:

            break;
        case MenuState::MenuItemLocal:
            game.runGame(window);
            break;
        case  MenuState::MenuItemAi:
            move.draw(window,mousePosition, map, currentPlayer);
            break;
        case  MenuState::MenuItemScores:
           game.runScore(window);
            break;
        case  MenuState::MenuItemExit:
            window.close();
            break;
    }
    return menuState;
}














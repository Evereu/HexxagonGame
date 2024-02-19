#pragma once
#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "../Logic/MenuState.h"
#include "../Logic/GameState.h"

class Menu {

public:
    Menu();
    ~Menu();

    auto draw(sf::RenderWindow &window, sf::Vector2<float> &mousePosition, MenuState &menuState) -> MenuState;
};




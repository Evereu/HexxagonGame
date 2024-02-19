#pragma once
#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "../Logic/MapStates.h"


class RenderMap {

public:
    RenderMap();

    ~RenderMap();

    auto renderHexagonMap() -> std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>>;

    auto rowPositions( sf::Vector2f position) -> std::vector<std::pair<sf::Vector2f ,sf::VertexArray>>;

    auto prepareGamePositions(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> renderMap) -> std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>>;
};



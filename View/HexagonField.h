#pragma once


class HexagonField {

public:

    HexagonField();

    ~ HexagonField();

    auto createHexagon(float x, float y) ->  sf::VertexArray;

    auto setPos(float x, float y) -> sf::Vector2f;
};

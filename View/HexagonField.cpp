#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "HexagonField.h"
#include <cmath>

HexagonField::HexagonField(){}

HexagonField::~HexagonField() {

}

auto HexagonField::createHexagon(float x, float y) -> sf::VertexArray{
    //https://en.sfml-dev.org/forums/index.php?topic=20555.0

    sf::CircleShape circle(35);
    circle.setPosition(HexagonField::setPos(x, y));

    sf::Vector2f circlePosition = circle.getPosition();
    float circleRadius = circle.getRadius();

    int numTriangles = 6;

    sf::VertexArray triangles(sf::Triangles);

    for (int i = 0; i < numTriangles; i++) {

        float angle1 = i * 2 * M_PI / numTriangles;
        float angle2 = (i + 1) * 2 * M_PI / numTriangles;

        sf::Vector2f point1(circlePosition.x + circleRadius * std::cos(angle1),
                            circlePosition.y + circleRadius * std::sin(angle1));

        sf::Vector2f point2(circlePosition.x + circleRadius * std::cos(angle2),
                            circlePosition.y + circleRadius * std::sin(angle2));

        triangles.append(sf::Vertex(circlePosition, sf::Color::Magenta));
        triangles.append(sf::Vertex(point1, sf::Color::Magenta));
        triangles.append(sf::Vertex(point2, sf::Color::Magenta));
    }
    return triangles;
}


auto HexagonField::setPos(float x, float y) -> sf::Vector2f {
    auto vec2f = sf::Vector2f(x,y);
    return vec2f;
}





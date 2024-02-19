#include "RenderMap.h"
#include "HexagonField.h"

RenderMap::RenderMap() {

}

RenderMap::~RenderMap(){

}

auto RenderMap::renderHexagonMap() -> std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> {

    std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> resultMap;
    std::vector<std::pair<MapStates, sf::Vector2f>> mapVector;

    for (int x = 0; x <= 8; x++) {
        for (int y = 0; y <= 18; y+=2) {
            sf::Vector2f positionVector = {static_cast<float>(x), static_cast<float>(y)};
            mapVector.push_back(std::make_pair(MapStates::Empty, positionVector));
        }
    }

    for (const auto &element: mapVector) {

        if (element.second.y >= 4 && element.second.y <= 12 && element.second.x == 0) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 4 && element.second.y <= 14 && element.second.x == 1) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 2 && element.second.y <= 14 && element.second.x == 2) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 2 && element.second.y <= 16 && element.second.x == 3) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions(element.second)));
        }
        if (element.second.y >= 0 && element.second.y <= 16 && element.second.x == 4) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 2 && element.second.y <= 16 && element.second.x == 5) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 2 && element.second.y <= 14 && element.second.x == 6) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions(element.second)));
        }
        if (element.second.y >= 4 && element.second.y <= 14 && element.second.x == 7) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
        if (element.second.y >= 4 && element.second.y <= 12 && element.second.x == 8) {
            resultMap.push_back(
                    std::make_pair(element.first, RenderMap::rowPositions( element.second)));
        }
    }

    resultMap = prepareGamePositions(resultMap);

    return resultMap;
}

auto RenderMap::prepareGamePositions(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> renderMap) -> std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>>{

    //środkowe zabronione pola
    renderMap.at(29).first = MapStates::Black;
    renderMap.at(39).first = MapStates::Black;
    renderMap.at(22).first = MapStates::Black;

    //Pola startowe gracz 1 czerwony
    renderMap.at(0).first = MapStates::PlayerOne;
    renderMap.at(34).first = MapStates::PlayerOne;
    renderMap.at(56).first = MapStates::PlayerOne;

    //Pola startowe gracz 2 zielony
    renderMap.at(4).first = MapStates::PlayerTwo;
    renderMap.at(26).first = MapStates::PlayerTwo;
    renderMap.at(60).first = MapStates::PlayerTwo;

    return renderMap;
}

auto RenderMap::rowPositions(sf::Vector2f position) ->  std::vector<std::pair<sf::Vector2f ,sf::VertexArray>> {

    std::vector<std::pair<sf::Vector2f ,sf::VertexArray>> resultVector;

    auto newHexagon  = HexagonField();

    auto hex = newHexagon.createHexagon( 300.f + static_cast<float>(position.x)* 75.f, 50+(static_cast<int>(position.x) % 2 ? static_cast<float>(position.y) * 40.f : 45+static_cast<float>(position.y) * 40.f));

    auto pairResult = std::make_pair(position, hex);

    resultVector.push_back(pairResult);

    return resultVector;
}
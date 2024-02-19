
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "MapStates.h"
#include "GameState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class Move {

public:

    Move();

    auto collision(const std::vector<sf::Vector2f>& availableMovesforOneStep, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f,  sf::VertexArray>>>> &renderMap, sf::Color color, MapStates player, MapStates enemy) -> void;

    auto draw(sf::RenderWindow &window, sf::Vector2<float> &mousePosition, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, GameState &gameState) -> void;

    auto showAvailableMoves(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, sf::Vector2<float> &mousePosition, GameState &gameState) -> int;

    auto findAvailableMovesForOneStep(sf::Vector2f positionClicked) -> std::vector<sf::Vector2f>;

    auto findAvailableMovesForTwoSteps(sf::Vector2f positionClicked) -> std::vector<sf::Vector2f>;

    auto showMovesOneStep(const std::vector<sf::Vector2f> &availableMovesforOneStep, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, sf::Color color, MapStates pawnType, GameState &gameState) -> void;

    auto showMovesTwoSteps(const std::vector<sf::Vector2f> &availableMovesforTwoSteps, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, sf::Color color, MapStates pawnType, GameState &gameState) -> void;

    auto makeMoveOne(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesforOneStep, sf::Vector2<float> &mousePosition, GameState &gameState) -> void;

    auto makeMoveTwo(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesForTwoSteps, std::vector<sf::Vector2f> &availableMovesforOneStep, sf::Vector2<float> &mousePosition, GameState &gameState) -> void;

    auto cancelMove(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesforOneStep, std::vector<sf::Vector2f> &availableMovesForTwoSteps) -> void;

    auto changePlayer(GameState &gameState) -> void;

    auto showPlayerPoints(sf::RenderWindow &window, std::string const &playerName, int playerPoints, sf::Color color, float width, float height) -> void;

    auto showBackground(sf::RenderWindow &window) -> void;

    auto showCurrentPlayer(sf::RenderWindow &window, std::string const &playerName, sf::Color color) -> void;

    auto endGameInfo(sf::RenderWindow &window, sf::Color color, int playerOnePoints, int playerTwoPoints)-> void;

    auto getPlayerOneElements() -> int;
    auto getPlayerTwoElements() -> int;

    auto setPlayerOneElements(int &elements) -> void;
    auto setPlayerTwoElements(int &elements) -> void;

private:

    int elementsOne;
    int elementsTwo;

    std::vector<MapStates> playerOneElements;
    std::vector<MapStates> playerTwoElements;

    sf::Font font;
    sf::Text text;
};

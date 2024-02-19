#include <map>
#include "Move.h"
#include "SFML/System/Vector2.hpp"
#include "fmt/core.h"
#include "MapStates.h"
#include "GameState.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SaveScore.h"

Move::Move() {

}

auto Move::getPlayerOneElements() -> int {

    return elementsOne;

}

auto Move::getPlayerTwoElements() -> int {

    return elementsTwo;
}

auto Move::setPlayerOneElements(int &elements) -> void {

    elementsOne = elements;
}

auto Move::setPlayerTwoElements(int &elements) -> void {

    elementsTwo = elements;

}

auto Move::showPlayerPoints(sf::RenderWindow &window, std::string const &playerName, int playerPoints, sf::Color color, float width, float height) -> void {

    if(!font.loadFromFile("../font/arialbd.ttf")){
        fmt::println("{}","Nie można załadować czcionki") ;
    }

    font.loadFromFile("../font/arialbd.ttf");

    //https://en.cppreference.com/w/cpp/string/basic_string/to_string
    auto playerPointsToString = std::to_string(playerPoints);

    sf::Text text(playerName+": " + playerPointsToString, font, 24);
    text.setFillColor(color);
    text.setPosition(window.getSize().x - text.getLocalBounds().width - width, height);

    window.draw(text);
}

    auto Move::showBackground(sf::RenderWindow &window) -> void {

        sf::Texture background;
        if (!background.loadFromFile("../Background/background.jpg")) {
            fmt::println("{}","Nie można zaladowac tla") ;
        }

        sf::Sprite backgroundSprite(background);
        backgroundSprite.setScale(static_cast<float>(window.getSize().x) / background.getSize().x,
                                  static_cast<float>(window.getSize().y) / background.getSize().y);

        window.draw(backgroundSprite);
}

auto  Move::showCurrentPlayer(sf::RenderWindow &window, std::string const &playerName, sf::Color color) -> void{

    if(!font.loadFromFile("../font/arialbd.ttf")){
        fmt::println("{}","Nie można załadować czcionki") ;
    }

    font.loadFromFile("../font/arialbd.ttf");

    sf::Text text(playerName, font, 24);
    text.setFillColor(color);

    text.setPosition(  50, 50);

    window.draw(text);

}

auto  Move::endGameInfo(sf::RenderWindow &window, sf::Color color, int playerOnePoints, int playerTwoPoints) -> void{

    SaveScore saveScore;

    if(!font.loadFromFile("../font/arialbd.ttf")){
        fmt::println("{}","Nie można załadować czcionki") ;
    }

    font.loadFromFile("../font/arialbd.ttf");

    sf::Text text ("Koniec gry", font, 50);
    text.setFillColor(color);

    float xpos = (window.getSize().x - text.getLocalBounds().width) / 2;
    float ypos = (window.getSize().y - text.getLocalBounds().height) / 2;
    text.setPosition(xpos, ypos);


    window.draw(text);

    if(playerOnePoints > playerTwoPoints){

        float x = (window.getSize().x - text.getLocalBounds().width) / 2;
        float y = (window.getSize().y - text.getLocalBounds().height) / 2 + 70;

        sf::Text text2 ("Wygrany: Czerwony", font, 30);

        text2.setFillColor(color);
        text2.setPosition(x, y);
        window.draw(text2);
    } else{

        float x = (window.getSize().x - text.getLocalBounds().width) / 2;
        float y = (window.getSize().y - text.getLocalBounds().height) / 2 + 70;

        sf::Text text2 ("Wygrany: Zielony", font, 30);

        text2.setFillColor(color);
        text2.setPosition(x, y);
        window.draw(text2);
    }

    int scorePlayerOne = getPlayerOneElements();
    int scorePlayerTwo = getPlayerTwoElements();

    saveScore.saveScore(scorePlayerOne, scorePlayerTwo);
}

auto Move::draw(sf::RenderWindow &window, sf::Vector2<float> &mousePosition, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, GameState &gameState) -> void{

    showBackground(window);

    auto score = showAvailableMoves(renderMap, mousePosition, gameState);

    for(const auto& mapInfo : renderMap){
        for(auto & hexagon : mapInfo.second){
            window.draw(hexagon.second);
        }
    }

    showPlayerPoints(window, "Czerwony", playerOneElements.size(), sf::Color::Red, 150, 50);
    showPlayerPoints(window, "Zielony", playerTwoElements.size(), sf::Color::Green, 150, 100);

    if(gameState.fieldState == MapStates::PlayerOne){
        showCurrentPlayer(window,"Tura gracza: Czerwony", sf::Color::Red);
    } else{
        showCurrentPlayer(window,"Tura gracza: Zielony", sf::Color::Green);
    }

    if(score > 57){

        endGameInfo(window, sf::Color::White, playerOneElements.size(), playerTwoElements.size());
    }
}


auto Move::showAvailableMoves(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, sf::Vector2<float> &mousePosition, GameState &gameState) -> int{

    std::vector<sf::Vector2f> availableMovesforOneStep;
    std::vector<sf::Vector2f> availableMovesForTwoSteps;

        for (auto &mapInfo: renderMap) {
            for (auto &hexagon: mapInfo.second) {
                if (mapInfo.first == MapStates::Black) {
                    for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                        hexagon.second[i].color = sf::Color::Transparent;
                    }
                }
                if (mapInfo.first == MapStates::PlayerOne) {
                    for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                        hexagon.second[i].color = sf::Color::Red;
                    }
                }
                if (mapInfo.first == MapStates::PlayerTwo) {
                    for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                        hexagon.second[i].color = sf::Color::Green;
                    }
                }
            }
        }

            for (auto &mapInfo: renderMap) {
                for (auto &hexagon: mapInfo.second) {

                    availableMovesforOneStep = findAvailableMovesForOneStep(hexagon.first);
                    availableMovesForTwoSteps = findAvailableMovesForTwoSteps(hexagon.first);

                        if (hexagon.second.getBounds().contains(mousePosition)) {

                            switch (mapInfo.first) {
                                case MapStates::PlayerOne:

                                    if(gameState.fieldState == MapStates::PlayerOne) {

                                        if (gameState.cancelState != 0) {
                                        cancelMove(renderMap, availableMovesforOneStep, availableMovesForTwoSteps);
                                            gameState.cancelState = 0;
                                           // return;
                                    } else{
                                            showMovesOneStep(availableMovesforOneStep, renderMap, sf::Color::Cyan,
                                                             MapStates::FirstLine, gameState);
                                            showMovesTwoSteps(availableMovesForTwoSteps, renderMap, sf::Color::Yellow,
                                                              MapStates::SecondLine, gameState);
                                         //  return;

                                            }
                                       }

                                    break;
                                case MapStates::PlayerTwo:

                                    if(gameState.fieldState == MapStates::PlayerTwo){
                                        if (gameState.cancelState != 0) {
                                            cancelMove(renderMap, availableMovesforOneStep, availableMovesForTwoSteps);
                                            gameState.cancelState = 0;
                                           // return;

                                        } else{
                                            showMovesOneStep(availableMovesforOneStep, renderMap, sf::Color::Cyan,
                                                             MapStates::FirstLine, gameState);
                                            showMovesTwoSteps(availableMovesForTwoSteps, renderMap, sf::Color::Yellow,
                                                              MapStates::SecondLine, gameState);
                                           // return;
                                        }
                                    }
                                    break;
                                case MapStates::Black:
                                    break;
                                case MapStates::Empty:
                                    break;
                                case MapStates::FirstLine:

                                    makeMoveOne(renderMap, availableMovesforOneStep, mousePosition,
                                                gameState);

                                    break;
                                case MapStates::SecondLine:
                                    makeMoveTwo(renderMap, availableMovesForTwoSteps, availableMovesforOneStep, mousePosition,
                                                gameState);
                                    break;
                            }
                        }
                }
            }

            playerOneElements.clear();
            playerTwoElements.clear();

    for(auto &i : renderMap){
        if(i.first == MapStates::PlayerOne) {
            playerOneElements.push_back(i.first);
        } else if (i.first == MapStates::PlayerTwo) {
            playerTwoElements.push_back(i.first);
        }
    }


    int score = playerOneElements.size() + playerTwoElements.size();

    if(score > 57){
        int scorePlayerOne = playerOneElements.size();
        int scorePlayerTwo = playerTwoElements.size();
        setPlayerOneElements(scorePlayerOne);
        setPlayerTwoElements(scorePlayerTwo);
    }

    return score;
}

     auto Move::cancelMove(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesforOneStep, std::vector<sf::Vector2f> &availableMovesForTwoSteps) -> void {

         for (auto &mapInfo: renderMap) {
             for (auto &hexagon: mapInfo.second) {
                 for(auto  &oneStep : availableMovesforOneStep ){
                     if(oneStep.x == hexagon.first.x && oneStep.y == hexagon.first.y) {
                         for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                             if (mapInfo.first != MapStates::PlayerOne && mapInfo.first != MapStates::PlayerTwo && mapInfo.first != MapStates::Black) {
                                 hexagon.second[i].color = sf::Color::Magenta;
                                 mapInfo.first = MapStates::Empty;
                             }
                         }
                     }
                 }

                 for(auto &twoStep : availableMovesForTwoSteps ){
                     if(twoStep.x == hexagon.first.x && twoStep.y == hexagon.first.y) {
                         for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                             if (mapInfo.first != MapStates::PlayerOne && mapInfo.first != MapStates::PlayerTwo && mapInfo.first != MapStates::Black) {
                                 hexagon.second[i].color = sf::Color::Magenta;
                                 mapInfo.first = MapStates::Empty;
                             }
                         }
                     }
                 }
             }
         }
         availableMovesforOneStep.clear();
    }

auto Move::changePlayer(GameState &gameState) -> void {
    if (gameState.fieldState == MapStates:: PlayerOne) {
        gameState.fieldState = MapStates::PlayerTwo;
    } else{
        gameState .fieldState= MapStates::PlayerOne;
    }
    gameState.cancelState = 0;
}

auto Move::findAvailableMovesForOneStep(sf::Vector2f positionClicked) -> std::vector<sf::Vector2f>{

    std::vector<sf::Vector2f> availableMovesForOneStep;

    //Skos góra prawo
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForOneStep.push_back({positionClicked.x + 1, positionClicked.y});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForOneStep.push_back({positionClicked.x + 1, positionClicked.y-2});
    }

    // bezposrednio dół
    availableMovesForOneStep.push_back({positionClicked.x, positionClicked.y + 2});

    // skos góra lewo
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForOneStep.push_back({positionClicked.x - 1, positionClicked.y});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForOneStep.push_back({positionClicked.x - 1, positionClicked.y-2});
    }

    // bezposrednio góra
    availableMovesForOneStep.push_back({positionClicked.x, positionClicked.y - 2});

    //skos w dół
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForOneStep.push_back({positionClicked.x - 1, positionClicked.y + 2 });
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForOneStep.push_back({positionClicked.x - 1, positionClicked.y});
    }

    //skos prawo dół
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForOneStep.push_back({positionClicked.x + 1, positionClicked.y + 2});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForOneStep.push_back({positionClicked.x + 1, positionClicked.y});
    }

    return availableMovesForOneStep;
}


auto Move::findAvailableMovesForTwoSteps(sf::Vector2f positionClicked) -> std::vector<sf::Vector2f>{

    std::vector<sf::Vector2f> availableMovesForTwoSteps;

    // w prawo
    availableMovesForTwoSteps.push_back({positionClicked.x + 2, positionClicked.y});

    // w dół
    availableMovesForTwoSteps.push_back({positionClicked.x, positionClicked.y+4});

    //w lewo
    availableMovesForTwoSteps.push_back({positionClicked.x - 2, positionClicked.y});

    //w górę
    availableMovesForTwoSteps.push_back({positionClicked.x, positionClicked.y - 4});

    // skos góra lewo
    availableMovesForTwoSteps.push_back({positionClicked.x - 2, positionClicked.y - 2});

    // skos dół prawo
    availableMovesForTwoSteps.push_back({positionClicked.x + 2, positionClicked.y + 2});

    // skos góra prawo
    availableMovesForTwoSteps.push_back({positionClicked.x + 2, positionClicked.y - 2});

    //skos góra prawo 2
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForTwoSteps.push_back({positionClicked.x + 1, positionClicked.y - 2});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForTwoSteps.push_back({positionClicked.x + 1, positionClicked.y - 4});
    }

    //skos góra lewo 2
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForTwoSteps.push_back({positionClicked.x - 1, positionClicked.y - 2});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForTwoSteps.push_back({positionClicked.x - 1, positionClicked.y - 4});
    }

    //skos dół lewo
    availableMovesForTwoSteps.push_back({positionClicked.x - 2, positionClicked.y + 2});

    //skos dół lewo 2
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForTwoSteps.push_back({positionClicked.x - 1, positionClicked.y + 4});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForTwoSteps.push_back({positionClicked.x - 1, positionClicked.y+2});
    }

    // skos dół prawo 2
    if(static_cast<int>(positionClicked.x) % 2 == 0){
        availableMovesForTwoSteps.push_back({positionClicked.x + 1, positionClicked.y + 4});
    }
    else if(static_cast<int>(positionClicked.x) % 2 != 0){
        availableMovesForTwoSteps.push_back({positionClicked.x + 1, positionClicked.y + 2});
    }

    return availableMovesForTwoSteps;
}

auto Move::collision(const std::vector<sf::Vector2f>& availableMovesforOneStep, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f,  sf::VertexArray>>>> &renderMap, sf::Color color, MapStates player, MapStates enemy) -> void {

    for (auto &mapInfo: renderMap) {
            if(mapInfo.first != MapStates::Black && mapInfo.first != player){
            for (auto &hexagon: mapInfo.second) {
                for(auto const &oneStep : availableMovesforOneStep ){
                    if(oneStep.x == hexagon.first.x && oneStep.y == hexagon.first.y && mapInfo.first == enemy){
                        mapInfo.first = player;
                        for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                            hexagon.second[i].color = color;
                        }
                    }
                }
            }
        }
    }
}

auto Move::showMovesOneStep(const std::vector<sf::Vector2f>& availableMovesforOneStep, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f,  sf::VertexArray>>>> &renderMap, sf::Color color, MapStates pawnType, GameState &gameState) -> void {
    for (auto &mapInfo: renderMap) {
        if ((mapInfo.first != MapStates::Black && mapInfo.first != MapStates::PlayerOne &&
             mapInfo.first != MapStates::PlayerTwo)) {
            for (auto &hexagon: mapInfo.second) {
                for (auto const &oneStep: availableMovesforOneStep) {
                    if (oneStep.x == hexagon.first.x && oneStep.y == hexagon.first.y) {
                        mapInfo.first = pawnType;
                        for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                            hexagon.second[i].color = color;
                        }
                    }
                }
            }
        }
    }
    gameState.cancelState++;
}

auto Move::showMovesTwoSteps(const std::vector<sf::Vector2f> &availableMovesforTwoSteps, std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, sf::Color color, MapStates pawnType, GameState &gameState) -> void {

    for (auto &mapInfo: renderMap) {
        if((mapInfo.first != MapStates::Black && mapInfo.first != MapStates::PlayerOne && mapInfo.first != MapStates::PlayerTwo)){
            for (auto &hexagon: mapInfo.second) {
                for(auto const &oneStep : availableMovesforTwoSteps ){
                    if(oneStep.x == hexagon.first.x && oneStep.y == hexagon.first.y){
                        mapInfo.first = pawnType;
                        for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                            hexagon.second[i].color = color;

                        }
                    }
                }
            }
        }
    }
    gameState.cancelState++;
}

 auto Move::makeMoveOne(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesforOneStep, sf::Vector2<float> &mousePosition, GameState &gameState) -> void {
     for (auto &mapInfo: renderMap) {
         for (auto &hexagon: mapInfo.second) {
             if (hexagon.second.getBounds().contains(mousePosition) && mapInfo.first == MapStates::FirstLine ) {
                 for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                     if (gameState.fieldState == MapStates::PlayerOne) {
                         hexagon.second[i].color = sf::Color::Red;
                         collision(availableMovesforOneStep, renderMap, sf::Color::Red, MapStates::PlayerOne, MapStates::PlayerTwo);
                     } else{
                         hexagon.second[i].color = sf::Color::Green;
                         collision(availableMovesforOneStep, renderMap, sf::Color::Green, MapStates::PlayerTwo, MapStates::PlayerOne);
                     }
                 }

                 mapInfo.first = gameState.fieldState;

                 for (auto &mapInfo: renderMap) {
                     for (auto &hexagon: mapInfo.second) {
                         if ((mapInfo.first != MapStates::Black) && (mapInfo.first != MapStates::PlayerOne) && (mapInfo.first != MapStates::PlayerTwo)) {
                             mapInfo.first = MapStates::Empty;
                             for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                                 hexagon.second[i].color = sf::Color::Magenta;
                                 mapInfo.first = MapStates::Empty;
                             }
                         }
                    }
                 }
             }
         }
     }
     availableMovesforOneStep.clear();
     changePlayer(gameState);
     }

auto Move::makeMoveTwo(std::vector<std::pair<MapStates, std::vector<std::pair<sf::Vector2f, sf::VertexArray>>>> &renderMap, std::vector<sf::Vector2f> &availableMovesForTwoSteps, std::vector<sf::Vector2f> &availableMovesforOneStep, sf::Vector2<float> &mousePosition, GameState &gameState) -> void {

    for (auto &mapInfo: renderMap) {
        for (auto &hexagon: mapInfo.second) {
            if (hexagon.second.getBounds().contains(mousePosition) && mapInfo.first == MapStates::SecondLine ) {
                    for (auto i = 0; i < hexagon.second.getVertexCount(); i++) {
                        if (gameState.fieldState == MapStates::PlayerOne) {
                            hexagon.second[i].color = sf::Color::Red;
                            collision(availableMovesforOneStep, renderMap, sf::Color::Red, MapStates::PlayerOne, MapStates::PlayerTwo);
                        } else {
                            hexagon.second[i].color = sf::Color::Green;
                            collision(availableMovesforOneStep, renderMap, sf::Color::Green, MapStates::PlayerTwo, MapStates::PlayerOne);
                        }
                    }

                    mapInfo.first = gameState.fieldState;

                for (auto &mapInfo: renderMap) {
                    for (auto &hexagon: mapInfo.second) {

                        if ((mapInfo.first != MapStates::Black) && (mapInfo.first != MapStates::PlayerOne) && (mapInfo.first != MapStates::PlayerTwo)) {
                            mapInfo.first = MapStates::Empty;
                            for (auto i = 0;
                                 i < hexagon.second.getVertexCount(); i++) {
                                hexagon.second[i].color = sf::Color::Magenta;
                            }
                        }
                    }
                }
            }
        }
    }
    availableMovesForTwoSteps.clear();
    changePlayer(gameState);
}
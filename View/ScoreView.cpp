#include <fstream>
#include "ScoreView.h"
#include "fmt/core.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../Logic/Move.h"
#include "SFML/Graphics/Sprite.hpp"

ScoreView::ScoreView(){};

ScoreView::~ScoreView(){};


auto ScoreView::drawScore(sf::RenderWindow &window)-> void{

    sf::Texture background;
    if (!background.loadFromFile("../Background/background.jpg")) {
    }
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / background.getSize().x,
                              static_cast<float>(window.getSize().y) / background.getSize().y);


    std::string content;

    try {
        std::ifstream file("../score.txt");

        if (!file.is_open()) {
            fmt::println("{}","Nie można załadować czcionki") ;

        }
        while (std::getline(file, content)) {
            fmt::println("{}",content) ;
        }
    } catch (const std::exception& e) {
        fmt::println("{}",e.what()) ;
    }


    if(!font.loadFromFile("../font/arial.ttf")){
        fmt::println("{}","Nie można załadować czcionki") ;
    }

    font.loadFromFile("../font/arial.ttf");

    auto playerOnePoints = std::to_string(content[0]);
    auto playerTwoPoints = std::to_string(content[1]);

    sf::Text text1("Gracz jeden: " + playerOnePoints, font, 24);
    text1.setPosition(100, 200);

    sf::Text text2("Gracz dwa: "+ playerTwoPoints, font, 24);
    text2.setPosition(100, 300);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(text1);
    window.draw(text2);
}
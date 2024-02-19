
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class ScoreView {

public:

    ScoreView();

    ~ScoreView();

    auto drawScore(sf::RenderWindow &window)-> void;

    sf::Font font;
    sf::Text text;
};


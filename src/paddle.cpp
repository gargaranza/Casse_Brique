
#include <iostream>
#include "paddle.hpp"


/*template <typename FontT, typename ShapeT>
std::function<sf::Vector2f(float)> Paddle<FontT, ShapeT>::getCurve(std::string nom) {
    switch (selectCourbe_.at(nom)) {
        case 0:
            return [&] (float x) {return sf::Vector2f{paddle_.getSize().x / 2 * x + (1-x) * (WINDOW_WIDTH - paddle_.getSize().x / 2), WINDOW_HEIGHT - 30};};
        default:
            return [&] (float x) {return sf::Vector2f{x*0 + WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30};};
    }
}*/


template <typename FontT, typename ShapeT>
void Paddle<FontT, ShapeT>::updatePosition(sf::Vector2f pos) {
    std::pair<sf::Vector2f, float> closest_position {courbe_(0), distance(pos, courbe_(0))};
    for (float x = 0.0 ; x < 1.0 ; x += 0.001) {
        if (distance(pos, courbe_(x)) < closest_position.second) 
            closest_position = {courbe_(x), distance(pos, courbe_(x))};
    }

    celerite_ = closest_position.first - centerPosition_;
    centerPosition_ = closest_position.first;

    setPaddlePosition();
}




#ifndef RECTANGLEPADDLE_H
#define RECTANGLEPADDLE_H

#include "global.h"
#include "paddle.hpp"


template <typename FontT>
class RectanglePaddle : public Paddle<FontT, sf::RectangleShape> {
    public:
        RectanglePaddle(FontT font, std::string nomCourbe, std::pair<float, float> taille): 
            Paddle<FontT, sf::RectangleShape>{font, sf::RectangleShape{{taille.first, taille.second}}, nomCourbe} {};

        const std::vector<sf::Vector2f> getCornerPoints() const override {
            sf::Vector2f cornerPosition {this->centerPosition_ - this->paddle_.getSize() / static_cast<float>(2)};
            return std::vector<sf::Vector2f> {
                cornerPosition, 
                cornerPosition + sf::Vector2f{this->paddle_.getSize().x, 0.0},
                cornerPosition + this->paddle_.getSize(),
                cornerPosition + sf::Vector2f{0.0, this->paddle_.getSize().y}
            };
        }

        inline bool isIn(sf::Vector2f vect) const override {return
            vect.x > (this->centerPosition_ - this->paddle_.getSize() / static_cast<float>(2)).x
            && vect.y > (this->centerPosition_ - this->paddle_.getSize() / static_cast<float>(2)).y
            && vect.x < (this->centerPosition_ + this->paddle_.getSize() / static_cast<float>(2)).x
            && vect.y < (this->centerPosition_ + this->paddle_.getSize() / static_cast<float>(2)).y;
        };

};



#endif //RECTANGLEPADDLE_H


#ifndef SQUAREBLOC_H
#define SQUAREBLOC_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include <iostream>
#include "global.h"
#include "bloc.hpp"
#include "blocType.hpp"

template <typename FontT>
class SquareBloc: public Bloc<sf::Vector2f, sf::RectangleShape, FontT, BlocType<FontT>> {
    public:
        SquareBloc() = delete;

        SquareBloc(sf::Vector2f pos, float c, FontT font, size_t pv);
        void draw();

        const std::vector<sf::Vector2f> getCornerPoints() const;
        const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getSides() const;
        inline bool isIn(sf::Vector2f vect) {return (
            vect.x > this->position_.x 
            && vect.y > this->position_.y 
            && vect.x < this->position_.x + this->forme_.getSize().x
            && vect.y < this->position_.y + this->forme_.getSize().y);
        };

        ~SquareBloc() = default;
};

#endif //SQUAREBLOC_H

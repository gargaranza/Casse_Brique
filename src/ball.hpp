#ifndef BALL
#define BALL

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include <iostream>
#include "global.h"
#include "ballType.hpp"

using Position = std::pair<size_t, size_t>;
using Speed = std::pair<int, int>;


template <typename FontT>
class Ball{
    private:
        BallType<FontT> type_;
        sf::CircleShape disk_;

        Position centerPosition_;
        Speed vitesse_;

        inline void setPosition() {disk_.setPosition(centerPosition_.first, centerPosition_.second);}

    public:
        Ball() = delete;
        inline Ball(BallType<FontT> type, Position position, Speed vitesse): type_{type}, centerPosition_{position}, vitesse_{vitesse} {
            disk_.setFillColor(type_.getFont());
            disk_.setRadius(type_.getRayon());
            setPosition();
        };

        ~Ball() = default;

        inline void setType(BallType<FontT> type) {type_ = type;};
        inline void updatePosition() {centerPosition_.first += vitesse_.first; centerPosition_.second += vitesse_.second; setPosition();};
        inline void setSpeed(Speed vitesse) {vitesse_ = vitesse;};

        inline Position getCenter() const {return centerPosition_;};
        inline size_t getRadius() const {return type_.getRayon();};
        inline Speed getSpeed() const {return vitesse_;};

        inline void draw() {window->draw(disk_); window->display();};
};

#endif //BALL

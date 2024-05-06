#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include <iostream>
#include "global.h"
#include "ballType.hpp"


template <typename FontT>
class Ball{
    private:
        BallType<FontT> type_;
        sf::CircleShape disk_;

        sf::Vector2f centerPosition_;
        sf::Vector2f vitesse_;

        inline void setPosition() {disk_.setPosition(centerPosition_ - sf::Vector2f{type_.getRayon(), type_.getRayon()});}

    public:
        Ball() = delete;
        inline Ball(BallType<FontT> type, sf::Vector2f position, sf::Vector2f vitesse): type_{type}, centerPosition_{position}, vitesse_{vitesse} {
            disk_.setFillColor(type_.getFont());
            disk_.setRadius(type_.getRayon());
            setPosition();
        };

        ~Ball() = default;

        inline void setType(BallType<FontT> type) {type_ = type;};
        inline void updatePosition() {centerPosition_ += vitesse_; setPosition(); };
        inline void setSpeed(sf::Vector2f vitesse) {vitesse_ = vitesse;};

        inline sf::Vector2f getCenter() const {return centerPosition_;};
        inline float getRadius() const {return type_.getRayon();};
        inline sf::Vector2f getSpeed() const {return vitesse_;};
        inline float getDamage() const {return type_.getDegats();};

        inline void draw() {window->draw(disk_); window->display();};

        friend std::ostream& operator<< <> (std::ostream& os, const Ball<FontT>& ball);

};

template <typename FontT>
std::ostream& operator<<(std::ostream& os, const Ball<FontT>& ball) {
    os << "(" << ball.centerPosition_.x << "," << ball.centerPosition_.y << "), (" << ball.vitesse_.x << "," << ball.vitesse_.y << ") " << &ball;
    return os;
};

#endif //BALL_H

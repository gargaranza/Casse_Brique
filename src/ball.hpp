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

        Position centerPosition_;
        Speed vitesse_;

    public:
        Ball() = delete;
        inline Ball(BallType<FontT> type, Position position, Speed vitesse): type_{type}, centerPosition_{position}, vitesse_{vitesse} {};

        ~Ball() = default;

        inline void setType(BallType<FontT> type) {type_ = type;};
        inline void updatePosition() {centerPosition_.first += vitesse_.first; centerPosition_.second += vitesse_.second;};
        inline void setSpeed(Speed vitesse) {vitesse_ = vitesse;};

        inline Position getCenter() const {return centerPosition_;};
        inline size_t getRadius() const {return type_.getRayon();};
        inline Speed getSpeed() const {return vitesse_;};

        void draw();
};

#endif //BALL

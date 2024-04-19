#ifndef BALL
#define BALL

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include "ballType.hpp"

using Position = std::pair<size_t, size_t>;
using Speed = std::pair<int, int>;


template <typename FontT>
class Ball{
    private:
        SDL_Surface* surface_;

        BallType<FontT> type_;

        Position CenterPosition_;
        Speed vitesse_;

    public:
        Ball() = delete;
        inline Ball(SDL_Surface* surface, BallType<FontT> type, Position position, Speed vitesse): 
            surface_{surface}, type_{type}, CenterPosition_{position}, vitesse_{vitesse} {};

        ~Ball() = default;

        inline void setType(BallType<FontT> type) {type_ = type;};
        inline void updatePosition() {CenterPosition_.first += vitesse_.first; CenterPosition_.second += vitesse_.second;};
        inline void setVitesse(Speed vitesse) {vitesse_ = vitesse;};

        void draw() const;
};

#endif //BALL

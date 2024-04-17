#ifndef BALL
#define BALL

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>

using Position = std::pair<size_t, size_t>;
using Speed = std::pair<int, int>;


template <typename FontT>
class Ball{
    private:
        SDL_Surface* surface_;

        BallType<FontT> type_;

        Position position_;
        Speed vitesse_;

    public:
        Ball() = delete;
        inline Ball(SDL_Surface* surface, BallType<FontT> type, Position position, Speed vitesse): 
            surface_{surface}, type_{type}, position_{position}, vitesse_{vitesse} {};

        ~Ball() = default;

        inline void setType(BallType<FontT> type) {type_ = type;};
        inline void updatePosition() {position_.first += vitesse_.first; position_.second += vitesse_.second;};
        inline void setVitesse(Speed vitesse) {vitesse_ = vitesse;};

        void draw();
};

#endif //BALL

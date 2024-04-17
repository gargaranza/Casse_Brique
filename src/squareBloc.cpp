
#include "squareBloc.hpp"

SquareBloc::SquareBloc(SDL_Surface* surface, std::pair<int, int> pos, size_t c, Uint32 color, size_t pv):
    Bloc{surface, pos, {pos.first, pos.second, static_cast<int>(c), static_cast<int>(c)}, {color, pv}, color, pv} 
{}

void SquareBloc::draw() const {
    if (PV_ > 0) {
        SDL_FillRect(surface_, &forme_, font_);
    }
}





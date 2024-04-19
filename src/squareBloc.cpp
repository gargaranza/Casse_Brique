
#include "squareBloc.hpp"

template <typename FontT>
SquareBloc<FontT>::SquareBloc(SDL_Surface* surface, std::pair<int, int> pos, size_t c, FontT font, size_t pv):
    Bloc<std::pair<int, int>, SDL_Rect, FontT, BlocType<FontT>>{
        surface, pos, {pos.first, pos.second, static_cast<int>(c), static_cast<int>(c)}, {font, pv}, font, pv} 
{;};

template <typename FontT>
void SquareBloc<FontT>::draw() const {
    if (this->PV_ > 0) {
        SDL_FillRect(this->surface_, &this->forme_, this->font_);
    }
};



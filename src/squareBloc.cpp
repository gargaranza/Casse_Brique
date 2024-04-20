
#include "squareBloc.hpp"

template <typename FontT>
SquareBloc<FontT>::SquareBloc(std::pair<int, int> pos, size_t c, FontT font, size_t pv):
    Bloc<std::pair<int, int>, SDL_Rect, FontT, BlocType<FontT>>{
        pos, {pos.first, pos.second, static_cast<int>(c), static_cast<int>(c)}, {font, pv}, font, pv} 
{};

template <typename FontT>
void SquareBloc<FontT>::draw() {
    if (!this->isBroken()) {
        Uint8 r {Uint8(255)};
        Uint8 g {Uint8(255)};
        Uint8 b {Uint8(255)};

        SDL_GetRGB(this->font_, win_surf->format, &r, &g, &b);
        SDL_SetRenderDrawColor(pRenderer, r, g, b, SDL_ALPHA_OPAQUE);

        SDL_RenderFillRect(pRenderer, &this->forme_);
    }
};



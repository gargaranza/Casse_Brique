
#include "ball.hpp"


template <typename FontT>
void Ball<FontT>::draw() {
    int x = 0;
    int y = type_.getRayon();
    int d = 3 - 2 * y;

    Uint8 r {Uint8(255)};
    Uint8 g {Uint8(255)};
    Uint8 b {Uint8(255)};

    SDL_GetRGB(type_.getFont(), win_surf->format, &r, &g, &b);
    SDL_SetRenderDrawColor(pRenderer, r, g, b, SDL_ALPHA_OPAQUE);

    while (x <= y) {
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first + x, centerPosition_.second + y);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first - x, centerPosition_.second + y);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first + x, centerPosition_.second - y);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first - x, centerPosition_.second - y);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first + y, centerPosition_.second + x);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first - y, centerPosition_.second + x);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first + y, centerPosition_.second - x);
        SDL_RenderDrawLine(pRenderer, centerPosition_.first, centerPosition_.second, centerPosition_.first - y, centerPosition_.second - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    SDL_UpdateWindowSurface(pWindow);
    SDL_RenderPresent(pRenderer);
};





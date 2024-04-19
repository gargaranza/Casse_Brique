#ifndef SQUAREBLOC_H
#define SQUAREBLOC_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include "bloc.hpp"
#include "blocType.hpp"

template <typename FontT>
class SquareBloc: public Bloc<std::pair<int, int>, SDL_Rect, FontT, BlocType<FontT>> {
    public:
        SquareBloc() = delete;

        SquareBloc(SDL_Surface* surface, std::pair<int, int> pos, size_t c, FontT font, size_t pv);
        void draw() const;

        ~SquareBloc() = default;
};

#endif //SQUAREBLOC_H

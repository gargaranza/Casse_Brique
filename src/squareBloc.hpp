#ifndef SQUAREBLOC_H
#define SQUAREBLOC_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include <iostream>
#include "global.h"
#include "bloc.hpp"
#include "blocType.hpp"

template <typename FontT>
class SquareBloc: public Bloc<std::pair<int, int>, sf::RectangleShape, FontT, BlocType<FontT>> {
    public:
        SquareBloc() = delete;

        SquareBloc(std::pair<int, int> pos, size_t c, FontT font, size_t pv);
        void draw();

        ~SquareBloc() = default;
};

#endif //SQUAREBLOC_H

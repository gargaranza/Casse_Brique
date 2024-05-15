#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <array>
#include <utility>
#include <iostream>
#include "global.h"
#include "blocContainer.hpp"
#include "blocType.hpp"
#include "squareBloc.hpp"

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
class Grid : public BlocContainer<width, height, SquareBloc<FontT>, FontT> {
    const float taille_;
    
    public:
        inline Grid(): BlocContainer<width, height, SquareBloc<FontT>, FontT>::BlocContainer{}, taille_{static_cast<float>(WINDOW_WIDTH - right_shift - left_shift)} {};

    private:
        SquareBloc<FontT>* createBloc(BlocType<FontT> type, size_t i, size_t j) override;
};

#endif //GRID_H



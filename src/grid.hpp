#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <array>
#include <utility>
#include "blocType.hpp"
#include "squareBloc.hpp"


template <size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
class Grid {
    std::array<std::array<SquareBloc*, height>, width> container_;
    SDL_Surface* surface_;
    const size_t taille_;

    public:
        inline Grid(SDL_Surface* surface): surface_{surface}, taille_{surface->w - right_shift - left_shift} {};

    private:
        SquareBloc* createBloc(BlocType<Uint32> type, size_t i, size_t j);
        
    public:
        void addBloc(BlocType<Uint32> type, size_t i, size_t j);

        void fillLine(BlocType<Uint32> type, size_t j);
        void fillLines(BlocType<Uint32> type, size_t nLines, ...);
        void fillColumn(BlocType<Uint32> type, size_t i);
        void fillColumns(BlocType<Uint32> type, size_t nColomns, ...);
        void fill(BlocType<Uint32> type);

        void draw() const;

        ~Grid();
};

#endif //GRID_H



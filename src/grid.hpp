#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <array>
#include <utility>
#include "blocContainer.hpp"
#include "blocType.hpp"
#include "squareBloc.hpp"

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
class Grid : public BlocContainer<std::array<std::array<SquareBloc<FontT>*, height>, width>> {
    const size_t taille_;
    
    public:
        inline Grid(SDL_Surface* surface): BlocContainer<std::array<std::array<SquareBloc<FontT>*, height>, width>>{surface}, taille_{surface->w - right_shift - left_shift} {};

    private:
        SquareBloc<FontT>* createBloc(BlocType<FontT> type, size_t i, size_t j);
        
    public:
        void addBloc(BlocType<FontT> type, size_t i, size_t j);

        void fillLine(BlocType<FontT> type, size_t j);
        void fillLines(BlocType<FontT> type, size_t nLines, ...);
        void fillColumn(BlocType<FontT> type, size_t i);
        void fillColumns(BlocType<FontT> type, size_t nColomns, ...);
        void fill(BlocType<FontT> type);

        void draw() const override;

        ~Grid();
};

#endif //GRID_H



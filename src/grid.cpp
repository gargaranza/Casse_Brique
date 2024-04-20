
#include <cstdarg>
#include <cassert>
#include <math.h>
#include "grid.hpp"


template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
SquareBloc<FontT>* Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::createBloc(BlocType<FontT> type, size_t i, size_t j) {
    return new SquareBloc{
        {left_shift + gap + taille_ / width * i + (taille_ - taille_/width * width) / 2, 
            top_shift + gap + taille_ / width * (height - j - 1)}, 
        taille_/width - gap, type.getFont(), type.getPV()
    };
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::addBloc(BlocType<FontT> type, size_t i, size_t j) {
    assert(i < width && j < height);
    this->container_.at(i).at(j) = createBloc(type, i, j);
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::fillLine(BlocType<FontT> type, size_t j) {
    for (size_t i = 0 ; i < width ; i++) {
        addBloc(type, i, j);
    }
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::fillLines(BlocType<FontT> type, size_t nLines, ...){
    va_list args;
    va_start(args, nLines);

    size_t j = va_arg(args, size_t);
    for (size_t k = 0; k < nLines; k++) {
        fillLine(type, j);
        j = va_arg(args, size_t);
    }

    va_end(args);
};


template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::fillColumn(BlocType<FontT> type, size_t i) {
    for (size_t j = 0 ; j < height ; j++) {
        addBloc(type, i, j);
    }
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::fillColumns(BlocType<FontT> type, size_t nColomns, ...){
    va_list args;
    va_start(args, nColomns);

    size_t i = va_arg(args, size_t);
    for (size_t k = 0; k < nColomns; k++) {
        fillColumn(type, i);
        i = va_arg(args, size_t);
    }

    va_end(args);
};


template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::fill(BlocType<FontT> type) {
    for (size_t i = 0 ; i < width ; i++) {
        for (size_t j = 0 ; j < height ; j++) {
            addBloc(type, i, j);
        }
    }
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
void Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::draw() const {
    for (size_t i = 0 ; i < width ; i++) {
        for (size_t j = 0 ; j < height ; j++) {
            this->container_.at(i).at(j)->draw();
        }
    }
};

template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::~Grid() {
    for (size_t i = 0 ; i < width ; i++) {
        for (size_t j = 0 ; j < height ; j++) {
            delete this->container_.at(i).at(j);
        }
    }
};


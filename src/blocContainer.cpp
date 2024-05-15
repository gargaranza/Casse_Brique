
#include <cstdarg>
#include <cassert>
#include <math.h>
#include "blocContainer.hpp"


template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::addBloc(BlocType<FontT> type, size_t i, size_t j) {
    assert(i < dim1 && j < dim2);
    container_.at(i).at(j) = createBloc(type, i, j);
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::fillLine(BlocType<FontT> type, size_t j) {
    for (size_t i = 0 ; i < dim1 ; i++) {
        addBloc(type, i, j);
    }
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::fillLines(BlocType<FontT> type, size_t nLines, ...){
    va_list args;
    va_start(args, nLines);

    size_t j = va_arg(args, size_t);
    for (size_t k = 0; k < nLines; k++) {
        fillLine(type, j);
        j = va_arg(args, size_t);
    }

    va_end(args);
};


template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::fillColumn(BlocType<FontT> type, size_t i) {
    for (size_t j = 0 ; j < dim2 ; j++) {
        addBloc(type, i, j);
    }
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::fillColumns(BlocType<FontT> type, size_t nColomns, ...){
    va_list args;
    va_start(args, nColomns);

    size_t i = va_arg(args, size_t);
    for (size_t k = 0; k < nColomns; k++) {
        fillColumn(type, i);
        i = va_arg(args, size_t);
    }

    va_end(args);
};


template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::fill(BlocType<FontT> type) {
    for (size_t i = 0 ; i < dim1 ; i++) {
        for (size_t j = 0 ; j < dim2 ; j++) {
            addBloc(type, i, j);
        }
    }
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
void BlocContainer<dim1, dim2, BlocT, FontT>::draw() const {
    for (size_t i = 0 ; i < dim1 ; i++) {
        for (size_t j = 0 ; j < dim2 ; j++) {
            container_.at(i).at(j)->draw();
        }
    }
    window->display();
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
std::vector<BlocT*> BlocContainer<dim1, dim2, BlocT, FontT>::getBlocs(){
    std::vector<BlocT*> retVect {};

    for (auto line : container_) {
        for (auto bloc : line) {
            retVect.push_back(bloc);
        }
    }

    return retVect;
};

template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
BlocContainer<dim1, dim2, BlocT, FontT>::~BlocContainer() {
    for (size_t i = 0 ; i < dim1 ; i++) {
        for (size_t j = 0 ; j < dim2 ; j++) {
            delete container_.at(i).at(j);
        }
    }
};



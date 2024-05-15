#ifndef BLOCCONTAINER_H
#define BLOCCONTAINER_H

#include <iostream>
#include "global.h"
#include "blocType.hpp"


template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
class BlocContainer {
    protected:
        std::array<std::array<BlocT*, dim2>, dim1> container_;

        virtual BlocT* createBloc(BlocType<FontT> type, size_t i, size_t j) = 0;

    public:
        ~BlocContainer();

        void addBloc(BlocType<FontT> type, size_t i, size_t j);

        void fillLine(BlocType<FontT> type, size_t j);
        void fillLines(BlocType<FontT> type, size_t nLines, ...);
        void fillColumn(BlocType<FontT> type, size_t i);
        void fillColumns(BlocType<FontT> type, size_t nColomns, ...);
        void fill(BlocType<FontT> type);

        std::vector<BlocT*> getBlocs();

        BlocT* getCase(size_t i, size_t j) {return this->container_.at(i).at(j);};

        void draw() const;
};

#endif //BLOCCONTAINER_H
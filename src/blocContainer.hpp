#ifndef BLOCCONTAINER_H
#define BLOCCONTAINER_H

#include <iostream>
#include "global.h"
#include "blocType.hpp"


template <size_t dim1, size_t dim2, typename BlocT, typename FontT>
class BlocContainer {
    protected:
        std::array<std::array<std::shared_ptr<BlocT>, dim2>, dim1> container_;

        virtual std::shared_ptr<BlocT> createBloc(const BlocType<FontT>& type, size_t i, size_t j) const = 0;

    public:
        //~BlocContainer();

        void addBloc(BlocType<FontT> type, size_t i, size_t j);

        void fillLine(BlocType<FontT> type, size_t j);
        void fillLines(BlocType<FontT> type, size_t nLines, ...);
        void fillColumn(BlocType<FontT> type, size_t i);
        void fillColumns(BlocType<FontT> type, size_t nColomns, ...);
        void fill(BlocType<FontT> type);

        std::vector<std::shared_ptr<BlocT>> getBlocs() const;

        std::shared_ptr<BlocT> getCase(size_t i, size_t j) const {return this->container_.at(i).at(j);};

        void draw() const;
};

#endif //BLOCCONTAINER_H
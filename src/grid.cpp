
#include "grid.hpp"


template <typename FontT, size_t width, size_t height, size_t left_shift, size_t right_shift, size_t top_shift, size_t gap>
std::shared_ptr<SquareBloc<FontT>> Grid<FontT, width, height, left_shift, right_shift, top_shift, gap>::createBloc(const BlocType<FontT>& type, size_t i, size_t j) const {
    return std::shared_ptr<SquareBloc<FontT>> {new SquareBloc{
        {left_shift + gap + taille_ / width * i,
            top_shift + gap + taille_ / width * (height - j - 1)}, 
        taille_/width - gap, type.getFont(), type.getPV()
    }};
};


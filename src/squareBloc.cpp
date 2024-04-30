
#include "squareBloc.hpp"

template <typename FontT>
SquareBloc<FontT>::SquareBloc(std::pair<int, int> pos, size_t c, FontT font, size_t pv):
    Bloc<std::pair<int, int>, sf::RectangleShape, FontT, BlocType<FontT>>{
        pos, sf::RectangleShape{}, {font, pv}, font, pv} {
    this->forme_.setSize(sf::Vector2f{static_cast<float>(c), static_cast<float>(c)});
    this->forme_.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));
    this->forme_.setFillColor(font);
};

template <typename FontT>
void SquareBloc<FontT>::draw() {
    if (!this->isBroken()) {
        window->draw(this->forme_);
    }
};



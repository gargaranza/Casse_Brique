
#include "squareBloc.hpp"

template <typename FontT>
SquareBloc<FontT>::SquareBloc(sf::Vector2f pos, float c, FontT font, size_t pv):
    Bloc<sf::Vector2f, sf::RectangleShape, FontT, BlocType<FontT>>{
        pos, sf::RectangleShape{}, {font, pv}, font, pv} {
    this->forme_.setSize(sf::Vector2f{c, c});
    this->forme_.setPosition(pos);
    this->forme_.setFillColor(font);
};

template <typename FontT>
void SquareBloc<FontT>::draw() {
    if (!this->isBroken()) {
        window->draw(this->forme_);
    }
};


template <typename FontT>
const std::vector<sf::Vector2f> SquareBloc<FontT>::getCornerPoints() const {
    return std::vector<sf::Vector2f> {
        this->position_, 
        this->position_ + sf::Vector2f{this->forme_.getSize().x, 0.0},
        this->position_ + this->forme_.getSize(),
        this->position_ + sf::Vector2f{0.0, this->forme_.getSize().y}
    };
};







#include "paddleManager.hpp"

template <typename FontT, typename ShapeT>
void PaddleManager<FontT, ShapeT>::move() {
    paddle_->updatePosition(paddle_->getPosition() + direction_ / (norme(direction_) == 0 ? 1 : norme(direction_)) * static_cast<float>(3.0));
};


template <typename FontT, typename ShapeT>
void PaddleManager<FontT, ShapeT>::setMousePosition(sf::Vector2f position) {};



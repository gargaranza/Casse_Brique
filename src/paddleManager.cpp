
#include "paddleManager.hpp"

template <typename FontT, typename ShapeT>
void PaddleManager<FontT, ShapeT>::move() {
    if (mouseUsed_) {
        paddle_->updatePosition(mousePosition_);
    } else {
        paddle_->updatePosition(paddle_->getPosition() + direction_ / (norme(direction_) == 0 ? 1 : norme(direction_)) * static_cast<float>(3.0));
    }
};




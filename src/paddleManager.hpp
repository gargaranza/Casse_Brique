#ifndef PADDLEMANAGER_H
#define PADDLEMANAGER_H

#include "paddle.hpp"

template <typename FontT, typename ShapeT>
class PaddleManager {
    private:
        Paddle<FontT, ShapeT>* const paddle_;
        sf::Vector2f direction_;

        sf::Vector2f mousePosition_;
        bool mouseUsed_;

        float norme(sf::Vector2f vect) {return std::sqrt(vect.x*vect.x + vect.y*vect.y);};

    public:
        PaddleManager() = default;
        inline PaddleManager(Paddle<FontT, ShapeT>* paddle): paddle_{paddle} {};
        void move();
        inline void drawPaddle() {paddle_->draw();};

        inline const Paddle<FontT, ShapeT>& getPaddle() const {return *paddle_;};

        inline void addUpDirection() {direction_ += sf::Vector2f {0.0, -1.0}; mouseUsed_ = false;};
        inline void addDownDirection() {direction_ += sf::Vector2f {0.0, 1.0}; mouseUsed_ = false;};
        inline void addLeftDirection() {direction_ += sf::Vector2f {-1.0, 0.0}; mouseUsed_ = false;};
        inline void addRightDirection() {direction_ += sf::Vector2f {1.0, 0.0}; mouseUsed_ = false;};

        inline void removeUpDirection() {direction_ -= sf::Vector2f {0.0, -1.0}; mouseUsed_ = false;};
        inline void removeDownDirection() {direction_ -= sf::Vector2f {0.0, 1.0}; mouseUsed_ = false;};
        inline void removeLeftDirection() {direction_ -= sf::Vector2f {-1.0, 0.0}; mouseUsed_ = false;};
        inline void removeRightDirection() {direction_ -= sf::Vector2f {1.0, 0.0}; mouseUsed_ = false;};

        inline void setMousePosition(sf::Vector2f position) {mousePosition_ = position; mouseUsed_ = true;};

        ~PaddleManager() = default;

};

#endif //PADDLEMANAGER_H
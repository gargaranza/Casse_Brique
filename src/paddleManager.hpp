#ifndef PADDLEMANAGER_H
#define PADDLEMANAGER_H

#include "paddle.hpp"

template <typename FontT, typename ShapeT>
class PaddleManager {
    private:
        Paddle<FontT, ShapeT>* const paddle_;
        sf::Vector2f direction_;

        float norme(sf::Vector2f vect) {return std::sqrt(vect.x*vect.x + vect.y*vect.y);};
        //float dotProd(sf::Vector2f v1, sf::Vector2f v2) {return v1.x*v2.x + v1.y*v2.y;};

    public:
        PaddleManager() = default;
        inline PaddleManager(Paddle<FontT, ShapeT>* paddle): paddle_{paddle} {};
        void move();
        inline void drawPaddle() {paddle_->draw();};

        inline const Paddle<FontT, ShapeT>& getPaddle() const {return *paddle_;};

        inline void addUpDirection() {direction_ += sf::Vector2f {0.0, -1.0};};
        inline void addDownDirection() {direction_ += sf::Vector2f {0.0, 1.0};};
        inline void addLeftDirection() {direction_ += sf::Vector2f {-1.0, 0.0};};
        inline void addRightDirection() {direction_ += sf::Vector2f {1.0, 0.0};};

        inline void removeUpDirection() {direction_ -= sf::Vector2f {0.0, -1.0};};
        inline void removeDownDirection() {direction_ -= sf::Vector2f {0.0, 1.0};};
        inline void removeLeftDirection() {direction_ -= sf::Vector2f {-1.0, 0.0};};
        inline void removeRightDirection() {direction_ -= sf::Vector2f {1.0, 0.0};};

        void setMousePosition(sf::Vector2f position);

        ~PaddleManager() = default;

};

#endif //PADDLEMANAGER_H
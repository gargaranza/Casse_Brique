#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include <memory>
#include <cstddef>
#include <iostream>
#include "ball.hpp"
#include "blocContainer.hpp"
#include "paddle.hpp"

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
class BallManager{
    private:
        Ball<FontTBall> ball_;
        std::shared_ptr<Paddle<FontTPad, ShapeT>> paddle_;
        std::shared_ptr<ContT> conteneur_;

        bool running_ = true;
        bool pause_ = true;

        float norme(const sf::Vector2f& vect) const {return std::sqrt(vect.x*vect.x + vect.y*vect.y);};
        float dotProd(const sf::Vector2f& v1, const sf::Vector2f& v2) const {return v1.x*v2.x + v1.y*v2.y;};
        void makeCollisions();
        bool isBallOutside() const;

        const sf::Vector2f intersection(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& M, const sf::Vector2f& V) const;
        const std::pair<bool, sf::Vector2f> collision(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& M, const sf::Vector2f& V) const;
        const sf::Vector2f updateSpeedCollision(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& V) const;
        const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getSidesFromPoints(const std::vector<sf::Vector2f>& corners) const;
    
    public:
        inline BallManager(Ball<FontTBall> &ball, std::shared_ptr<ContT> conteneur, std::shared_ptr<Paddle<FontTPad, ShapeT>> paddle): ball_{ball}, paddle_{paddle}, conteneur_{conteneur} {/*std::cout << "Ball manager :" << this << ", ball :" << ball_ << std::endl;*/};

        void run();
        inline void start() {running_ = true; pause_ = false;};
        inline void pause() {pause_ = true;};
        inline void stop() {running_ = false;};

        inline bool isStoped() const {return !running_;};
        inline void drawBall() const {ball_.draw();};

        inline const Ball<FontTBall>& getBall() const {return ball_;};

};


#endif //BALLMANAGER_H



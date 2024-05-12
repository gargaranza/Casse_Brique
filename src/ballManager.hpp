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
        const Paddle<FontTPad, ShapeT>* const paddle_;
        ContT* conteneur_;

        bool running = true;

        float norme(sf::Vector2f vect) {return std::sqrt(vect.x*vect.x + vect.y*vect.y);};
        float dotProd(sf::Vector2f v1, sf::Vector2f v2) {return v1.x*v2.x + v1.y*v2.y;};
        void makeCollisions();
        sf::Vector2f intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V);
        std::pair<bool, sf::Vector2f> collision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V);
        sf::Vector2f updateSpeedCollision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f V);
        const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getSidesFromPoints(std::vector<sf::Vector2f> corners) const;
    
    public:
        inline BallManager(Ball<FontTBall> &ball, ContT* conteneur, const Paddle<FontTPad, ShapeT>* paddle): ball_{ball}, paddle_{paddle}, conteneur_{conteneur} {/*std::cout << "Ball manager :" << this << ", ball :" << ball_ << std::endl;*/};

        void run();
        inline void stop() {running = false;};
        inline void drawBall() {ball_.draw();};

        inline const Ball<FontTBall>& getBall() const {return ball_;};

};


#endif //BALLMANAGER_H



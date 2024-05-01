#ifndef BALLMANAGER
#define BALLMANAGER

#include <memory>
#include <cstddef>
#include <iostream>
#include "ball.hpp"
#include "blocContainer.hpp"

template <typename FontT, typename ContT>
class BallManager{
    private:
        Ball<FontT> ball_;
        ContT* conteneur_;

        bool running = true;

        void makeCollisions();
        inline float length(sf::Vector2f vect) {return std::sqrt(vect.x * vect.x + vect.y * vect.y);};
        inline float dotProd(sf::Vector2f v1, sf::Vector2f v2) {return v1.x*v2.x + v1.y*v2.y;};
        sf::Vector2f intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V);
        std::pair<bool, sf::Vector2f> collision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V);
        sf::Vector2f updateSpeedCollision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f V);
    
    public:
        inline BallManager(Ball<FontT> &ball, ContT* conteneur): ball_{ball}, conteneur_{conteneur} {/*std::cout << "Ball manager :" << this << ", ball :" << ball_ << std::endl;*/};

        void run();
        inline void stop() {running = false;};
        inline void drawBall() {ball_.draw();};

};


#endif //BALLMANAGER



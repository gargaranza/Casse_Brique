
#include <thread>
#include <chrono>
#include "ballManager.hpp"


template <typename BallT, typename ContT>
sf::Vector2f BallManager<BallT, ContT>::intersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V) {

    float det = (A.y - B.y)*V.x + (B.x - A.x) * V.y;
    sf::Vector2f P {A.x*(B.y-A.y) - A.y*(B.x-A.x), M.x*V.y - M.y*V.x};
    if (std::abs(det) > 10e-10) {
        sf::Vector2f X {((B.x - A.x)*P.y - V.x*P.x)/det, ((B.y - A.y)*P.y - V.y * P.x)/det};
        if (X.x < std::min(A.x, B.x) - 0.1 || X.x > std::max(A.x, B.x) + 0.1 || X.y < std::min(A.y, B.y) - 0.1 || X.y > std::max(A.y, B.y) + 0.1){
            return sf::Vector2f{};
        }
        return X;
    }
    return sf::Vector2f{};
};

template <typename BallT, typename ContT>
std::pair<bool, sf::Vector2f> BallManager<BallT, ContT>::collision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f M, sf::Vector2f V) {
    sf::Vector2f X {intersection(A, B, M, V)};

    /*if (X != sf::Vector2f{}) {
        std::cout << "X: (" << X.x << "," << X.y << ")\n";
        std::cout << "A: (" << A.x << "," << A.y << ")\n";
        std::cout << "B: (" << B.x << "," << B.y << ")\n";
        std::cout << "M: (" << M.x << "," << M.y << ")\n";
        std::cout << "V: (" << V.x << "," << V.y << ")" << std::endl;
    }*/

    if (X == sf::Vector2f{}) return std::pair<bool, sf::Vector2f> {false, X};
    else {
        float d = std::sqrt((X.x - M.x)*(X.x - M.x) + (X.y - M.y)*(X.y - M.y));
        float s = (X - M).x*V.x + (X - M).y*V.y;
        if ((d <= 1.1 * std::sqrt(V.x*V.x + V.y*V.y)) && (s > 10e-8)) {
            return std::pair<bool, sf::Vector2f> {true, X};
        } else return std::pair<bool, sf::Vector2f> {false, sf::Vector2f{}};
    }
};

template <typename BallT, typename ContT>
sf::Vector2f BallManager<BallT, ContT>::updateSpeedCollision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f V) {
    sf::Vector2f U {A-B};
    float d = std::sqrt(U.x * U.x + U.y * U.y);
    U = sf::Vector2f {U.y/d, -U.x/d};
    float ps = V.x*U.x + V.y*U.y;
    return V-2*ps*U;
}



template <typename BallT, typename ContT>
void BallManager<BallT, ContT>::makeCollisions() {
    //Border collisions
    if (ball_.getCenter().x + ball_.getRadius() >= static_cast<float>(WINDOW_WIDTH) || 
        ball_.getCenter().x - ball_.getRadius() <= 0.0) {
        ball_.setSpeed({-ball_.getSpeed().x, ball_.getSpeed().y});
    }
    if (ball_.getCenter().y + ball_.getRadius() >= static_cast<float>(WINDOW_HEIGHT) || 
        ball_.getCenter().y - ball_.getRadius() <= 0.0) {
        ball_.setSpeed({ball_.getSpeed().x, -ball_.getSpeed().y});
    }

    //Blocs collision
    for (auto bloc : conteneur_->getBlocs()) {
        if (bloc->isBroken()) continue;
        const std::vector<sf::Vector2f> blocCorners = bloc->getCornerPoints();
        const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> blocSides = bloc->getSides();

        for (std::pair<sf::Vector2f, sf::Vector2f> side : blocSides) {
            auto col {collision(side.first, side.second, ball_.getCenter(), ball_.getSpeed())};
            if (col.first && !(bloc->isIn(ball_.getCenter()))) {
                ball_.setSpeed(updateSpeedCollision(side.first, side.second, ball_.getSpeed()));
                bloc->takeDamage(ball_.getDamage());
            }
        }
    }
}


template <typename BallT, typename ContT>
void BallManager<BallT, ContT>::run(){
    running = true;
    //std::cout << "Running" << std::endl;
    auto now = std::chrono::steady_clock::now();
    while (running) {
        makeCollisions();
        ball_.updatePosition();
        std::this_thread::sleep_until(now + std::chrono::milliseconds(3));
        now = std::chrono::steady_clock::now();
    }
    //std::cout << "End Running" << std::endl;
};




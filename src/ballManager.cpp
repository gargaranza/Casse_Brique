
#include <thread>
#include <chrono>
#include "ballManager.hpp"

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
const sf::Vector2f BallManager<FontTBall, FontTPad, ContT, ShapeT>::intersection(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& M, const sf::Vector2f& V) const {

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

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
const std::pair<bool, sf::Vector2f> BallManager<FontTBall, FontTPad, ContT, ShapeT>::collision(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& M, const sf::Vector2f& V) const {
    sf::Vector2f X {intersection(A, B, M, V)};

    if (X == sf::Vector2f{}) return std::pair<bool, sf::Vector2f> {false, X};
    else {
        float d = norme(X-M);
        float s = (X - M).x*V.x + (X - M).y*V.y;
        if ((d <= 1.1 * std::sqrt(V.x*V.x + V.y*V.y)) && (s > 10e-8)) {
            return std::pair<bool, sf::Vector2f> {true, X};
        } else return std::pair<bool, sf::Vector2f> {false, sf::Vector2f{}};
    }
};

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
const sf::Vector2f BallManager<FontTBall, FontTPad, ContT, ShapeT>::updateSpeedCollision(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& V) const {
    sf::Vector2f U {A-B};
    float d = norme(U);
    U = sf::Vector2f {U.y/d, -U.x/d};
    float ps = dotProd(V, U);
    return V-2*ps*U;
}

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> BallManager<FontTBall, FontTPad, ContT, ShapeT>::getSidesFromPoints(const std::vector<sf::Vector2f>& corners) const {
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> sides;
    sf::Vector2f last_point = corners.at(corners.size() - 1);
    for (sf::Vector2f point : corners){
        sides.push_back(std::pair<sf::Vector2f, sf::Vector2f> {last_point, point});
        last_point = point;
    }

    return sides;
}


template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
void BallManager<FontTBall, FontTPad, ContT, ShapeT>::makeCollisions() {
    //Border collisions
    if (ball_.getCenter().x + ball_.getRadius() >= static_cast<float>(WINDOW_WIDTH)) {
        ball_.setSpeed({-std::abs(ball_.getSpeed().x), ball_.getSpeed().y});
    }
    else if (ball_.getCenter().x - ball_.getRadius() <= 0.0) {
        ball_.setSpeed({std::abs(ball_.getSpeed().x), ball_.getSpeed().y});
    }
    else if (ball_.getCenter().y - ball_.getRadius() <= 0.0) {
        ball_.setSpeed({ball_.getSpeed().x, std::abs(ball_.getSpeed().y)});
    }
    /*else if (ball_.getCenter().y + ball_.getRadius() >= static_cast<float>(WINDOW_HEIGHT)) {
        ball_.setSpeed({ball_.getSpeed().x, -std::abs(ball_.getSpeed().y)});
    }*/


    //Blocs collision
    for (auto &bloc : conteneur_->getBlocs()) {
        if (bloc->isBroken()) continue;
        for (std::pair<sf::Vector2f, sf::Vector2f> side : getSidesFromPoints(bloc->getCornerPoints())) {
            sf::Vector2f U {side.first-side.second};
            float d = norme(U);
            U = U/d * ball_.getRadius();
            std::vector<sf::Vector2f> points {
                {ball_.getCenter() - sf::Vector2f{U.y/d, U.x/d}}, 
                {ball_.getCenter() + sf::Vector2f{U.y/d, U.x/d}},
                {ball_.getCenter() - U},
                {ball_.getCenter() + U}
            };
            for (sf::Vector2f p : points) {
                auto col {collision(side.first, side.second, p, ball_.getSpeed())};
                if (col.first && !(bloc->isIn(p))) {
                    ball_.setSpeed(updateSpeedCollision(side.first, side.second, ball_.getSpeed()));
                    bloc->takeDamage(ball_.getDamage());
                }
            }
        }
    }


    //Paddle collision
    for (std::pair<sf::Vector2f, sf::Vector2f> side : getSidesFromPoints(paddle_->getCornerPoints())) {
        sf::Vector2f U {side.first-side.second};
        float d = norme(U);
        U = U/d * ball_.getRadius();
        std::vector<sf::Vector2f> points {
            {ball_.getCenter() - sf::Vector2f{U.y/d, U.x/d}}, 
            {ball_.getCenter() + sf::Vector2f{U.y/d, U.x/d}},
            {ball_.getCenter() - U},
            {ball_.getCenter() + U}
        };
        for (sf::Vector2f p : points) {
            auto col {collision(side.first, side.second, p, ball_.getSpeed())};
            if (col.first && !(paddle_->isIn(p))) {
                ball_.setSpeed(updateSpeedCollision(side.first, side.second, ball_.getSpeed()) + paddle_->getSpeed() * static_cast<float>(0.10));
            }
        }
    }
}

template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
bool BallManager<FontTBall, FontTPad, ContT, ShapeT>::isBallOutside() const {
    return (ball_.getCenter().x - 5*ball_.getRadius() >= static_cast<float>(WINDOW_WIDTH)) || 
        (ball_.getCenter().x + 5*ball_.getRadius() <= 0.0) || 
        (ball_.getCenter().y - 5*ball_.getRadius() >= static_cast<float>(WINDOW_WIDTH)) || 
        (ball_.getCenter().y + 5*ball_.getRadius() <= 0.0);
}


template <typename FontTBall, typename FontTPad, typename ContT, typename ShapeT>
void BallManager<FontTBall, FontTPad, ContT, ShapeT>::run(){
    running_ = true;
    //std::cout << "Running" << std::endl;
    auto now = std::chrono::steady_clock::now();
    while (running_) {
        if (isBallOutside()) stop();
        if (!pause_) {
            makeCollisions();
            ball_.updatePosition();
        }
        std::this_thread::sleep_until(now + std::chrono::milliseconds(3));
        now = std::chrono::steady_clock::now();
    }
    //std::cout << "End Running" << std::endl;
};




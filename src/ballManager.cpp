
#include <thread>
#include <chrono>
#include "ballManager.hpp"

template <typename BallT, typename ContT>
void BallManager<BallT, ContT>::run(){
    running = true;
    std::cout << "Running" << std::endl;
    while (running) {
        if (static_cast<int>(ball_.getCenter().first) + static_cast<int>(ball_.getRadius()) >= WINDOW_WIDTH || 
            static_cast<int>(ball_.getCenter().first) - static_cast<int>(ball_.getRadius()) <= 0) {
            ball_.setSpeed({-ball_.getSpeed().first, ball_.getSpeed().second});
        }
        if (static_cast<int>(ball_.getCenter().second) + static_cast<int>(ball_.getRadius()) >= WINDOW_HEIGHT || 
            static_cast<int>(ball_.getCenter().second) - static_cast<int>(ball_.getRadius()) <= 0) {
            ball_.setSpeed({ball_.getSpeed().first, -ball_.getSpeed().second});
        }
        ball_.updatePosition();
        window->clear();
        conteneur_->draw();
        ball_.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    std::cout << "\nEnd Running" << std::endl;
};




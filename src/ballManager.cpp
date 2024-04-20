
#include "ballManager.hpp"

template <typename BallT, typename ContT>
void BallManager<BallT, ContT>::run(size_t delay){
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
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
        ball_.updatePosition();
        conteneur_->draw();
        ball_.draw();
        SDL_RenderPresent(pRenderer);

        SDL_Delay(delay);
        std::cout << "!";
    }
    std::cout << "\nEnd Running" << std::endl;
};




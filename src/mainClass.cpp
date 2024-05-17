
#include "mainClass.hpp"

template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
MainClass<BlocFontT, BlocT, dim1, dim2, BallFontT, PaddleFontT, PaddleShapeT>::MainClass() : 
    blocTypes_ {
        {"faible", {sf::Color{0, 0, 200}, 10}}, 
        {"moyen", {sf::Color{200, 0, 0}, 20}},
        {"resistant", {sf::Color{150, 150, 150}, 50}},
        {"invincible", {sf::Color{0, 0, 0}, 1000000}}
    }, 
    ballTypes_ {
        {"classique", {sf::Color{120, 255, 0}, 5, 10}}
    }, 
    container_ {new Grid<BlocFontT, dim1, dim2, 0, 0, 0, 1>{}},
    paddle_ {new RectanglePaddle<PaddleFontT> {sf::Color{255, 127, 0}, std::string{"Ligne"}, {150, 10}}}, 
    paddleManager_ {paddle_},
    running_{false},
    pause_{false}
{};


template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
void MainClass<BlocFontT, BlocT, dim1, dim2, BallFontT, PaddleFontT, PaddleShapeT>::loadGrille(const std::string fileName) {
    if (fileName == "") {
        container_->fill(blocTypes_.at("invincible"));
        container_->fillLines(blocTypes_.at("faible"), 4, 0, 1, 2, 3);
        container_->fillLines(blocTypes_.at("moyen"), 3, 4, 5, 6);
        container_->fillLines(blocTypes_.at("resistant"), 2, 7, 8);
    }
}


template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
void MainClass<BlocFontT, BlocT, dim1, dim2, BallFontT, PaddleFontT, PaddleShapeT>::addNewBall(const BallType<BallFontT> type) {
    auto ballMana = std::shared_ptr<BallManager<BallFontT, PaddleFontT, BlocContainer<dim1, dim2, BlocT, BlocFontT>, PaddleShapeT>> {new BallManager<BallFontT, PaddleFontT, BlocContainer<dim1, dim2, BlocT, BlocFontT>, PaddleShapeT> {
        *new Ball<BallFontT> {
            type, 
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, 
            [](float r, float speed){return sf::Vector2f{speed * r, speed * -std::sqrt(1-r*r)};} ((float)(rand()) / (float)(RAND_MAX), 1.5)
        }, 
        container_,
        paddle_
    }};
    ballManagers_.push_back(ballMana);
    std::unique_ptr<std::thread> thPtr = std::make_unique<std::thread>([ballMana] () {ballMana->run();});
    ballThreads_.push_back(std::move(thPtr));
}

template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
void MainClass<BlocFontT, BlocT, dim1, dim2, BallFontT, PaddleFontT, PaddleShapeT>::triggerEvents() {
    sf::Event event;
    while(window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                running_ = false;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        paddleManager_.addLeftDirection();
                        break;
                    case sf::Keyboard::Right:
                        paddleManager_.addRightDirection();
                        break;
                    case sf::Keyboard::Up:
                        paddleManager_.addUpDirection();
                        break;
                    case sf::Keyboard::Down:
                        paddleManager_.addDownDirection();
                        break;
                    case sf::Keyboard::Escape:
                        pause_ = !pause_;
                        for (auto manager : ballManagers_) if (manager != nullptr) (pause_ ? manager->pause() : manager->start());
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        paddleManager_.removeLeftDirection();
                        break;
                    case sf::Keyboard::Right:
                        paddleManager_.removeRightDirection();
                        break;
                    case sf::Keyboard::Up:
                        paddleManager_.removeUpDirection();
                        break;
                    case sf::Keyboard::Down:
                        paddleManager_.removeDownDirection();
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseMoved:
                paddleManager_.setMousePosition(sf::Vector2f{static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)});
                break;
            default:
                break;
        }
    }
}


template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
void MainClass<BlocFontT, BlocT, dim1, dim2, BallFontT, PaddleFontT, PaddleShapeT>::run() {
    for (size_t i = 0; i < 3; i++) {
        addNewBall(ballTypes_.at("classique"));
    }

    running_ = true;

    for (auto manager : ballManagers_) if (manager != nullptr) manager->start();
    while(running_) {
        triggerEvents();
        if (!pause_) {
            window->clear(sf::Color{15, 5, 107});
            container_->draw();
            paddleManager_.move();
            paddleManager_.drawPaddle();
            for (auto manager : ballManagers_) {
                if (manager != nullptr) manager->drawBall();
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if (!pause_) {
            bool stop = true;
            for (auto& manager : ballManagers_) if (manager != nullptr && !manager->isStoped()) stop = false;
            if (stop) {
                running_ = false;
                std::cout << "Stopping" << std::endl;
            }
        }
    }

    for (auto manager : ballManagers_) if (manager != nullptr) manager->stop();
    for (auto& thread : ballThreads_) if (thread != nullptr) thread->join();

    window->setActive(false);
};








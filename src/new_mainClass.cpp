
#include "new_mainClass.hpp"


MainClass::MainClass() : 
    blocTypes_ {
        {"faible", {sf::Color{0, 0, 200}, 10}}, 
        {"moyen", {sf::Color{200, 0, 0}, 20}},
        {"resistant", {sf::Color{150, 150, 150}, 50}},
        {"invincible", {sf::Color{0, 0, 0}, 1000000}}
    }, 
    ballTypes_ {
        {"classique", {sf::Color{120, 255, 0}, 5, 10}}
    }, 
    container_ {new Grille{}},
    paddle_ {new RectanglePaddle<PaddleFontType> {sf::Color{255, 127, 0}, std::string{"Ligne"}, {300, 10}}}, 
    paddleManager_ {paddle_.get()},
    running_{False}
{};


void MainClass::loadGrille(const std::string fileName) {
    if (fileName == "") {
        container_->fill(blocTypes_.at("invincible"));
        container_->fillLines(blocTypes_.at("faible"), 4, 0, 1, 2, 3);
        container_->fillLines(blocTypes_.at("moyen"), 3, 4, 5, 6);
        container_->fillLines(blocTypes_.at("resistant"), 2, 7, 8);
    }
}


void MainClass::run() {
    for (size_t i = 0; i < 2; i++) {
        addNewBall(ballTypes_.at("classique"));
    }

    running_ = true;

    while(running_) {
        triggerEvents();
        window->clear(sf::Color{15, 5, 107});
        container_->draw();
        paddleManager_.move();
        paddleManager_.drawPaddle();
        for (auto manager : ballManagers_) {
            if (manager != nullptr) manager->drawBall();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    for (auto manager : ballManagers_) if (manager != nullptr) manager->stop();
    for (auto& thread : ballThreads_) if (thread != nullptr) thread->join();

    window->setActive(false);
};


void MainClass::addNewBall(const BallType<BallFontType> type) {
    auto ballMana = std::shared_ptr<BallManager<BallFontType, PaddleFontType, BlocContainer<dim1, dim2, BlocT, BlocFontType>, PaddleShapeType>> {new BallManager<BallFontType, PaddleFontType, BlocContainer<dim1, dim2, BlocT, BlocFontType>, PaddleShapeType> {
        *new Ball<BallFontType> {
            type, 
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, 
            [](float r, float speed){return sf::Vector2f{speed * r, speed * -std::sqrt(1-r*r)};} ((float)(rand()) / (float)(RAND_MAX), 1.2)
        }, 
        container_,
        paddle_
    }};
    ballManagers_.push_back(std::move(ballMana));
    std::unique_ptr<std::thread> thPtr = std::make_unique<std::thread>([ballMana] () {ballMana->run();});
    ballThreads_.push_back(std::move(thPtr));
}

void MainClass::triggerEvents() {
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
            default:
                break;
        }
    }
}






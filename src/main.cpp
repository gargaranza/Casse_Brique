#include <utility>
#include <cstddef>
#include <cstdlib>
#include <array>
#include <set>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

#include "global.h"
#include "squareBloc.cpp"
#include "blocType.hpp"
#include "blocContainer.cpp"
#include "grid.cpp"
#include "paddle.cpp"
#include "rectanglePaddle.hpp"
#include "ball.hpp"
#include "ballManager.cpp"
#include "paddleManager.cpp"

const std::shared_ptr<sf::RenderWindow> window {new sf::RenderWindow{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Casse Brique"}};

using BlocFontType = sf::Color;
using BallFontType = sf::Color;
using PaddleFontType = sf::Color;
using PaddleShapeType = sf::RectangleShape;
using Grille = Grid<BlocFontType, 33, 12, 0, 0, 0, 1>;
using ContainerType = Grille;

void addNewBall(Grille &grille, const Paddle<PaddleFontType, PaddleShapeType>& paddle, std::vector<BallManager<BallFontType, PaddleFontType, ContainerType, PaddleShapeType>*> &ballManagers, std::vector<std::unique_ptr<std::thread>> &ballThreads, const BallType<BallFontType> type) {
    auto ballMana = new BallManager<BallFontType, PaddleFontType, ContainerType, PaddleShapeType> {
        *new Ball<BallFontType> {
            type, 
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, 
            [](float r, float speed){return sf::Vector2f{speed * r, speed * -std::sqrt(1-r*r)};} ((float)(rand()) / (float)(RAND_MAX), 2)
        }, 
        &grille,
        &paddle
    };
    ballManagers.push_back(std::move(ballMana));
    std::unique_ptr<std::thread> thPtr = std::make_unique<std::thread>([ballMana] () {ballMana->run();});
    ballThreads.push_back(std::move(thPtr));
}

void triggerEvents(bool& running, bool& pause, PaddleManager<PaddleFontType, PaddleShapeType>& plateauManager, std::vector<BallManager<BallFontType, PaddleFontType, ContainerType, PaddleShapeType>*>& ballManagers) {
    sf::Event event;
    while(window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        plateauManager.addLeftDirection();
                        break;
                    case sf::Keyboard::Right:
                        plateauManager.addRightDirection();
                        break;
                    case sf::Keyboard::Up:
                        plateauManager.addUpDirection();
                        break;
                    case sf::Keyboard::Down:
                        plateauManager.addDownDirection();
                        break;
                    case sf::Keyboard::Escape:
                        pause = !pause;
                        for (auto manager : ballManagers) if (manager != nullptr) (pause ? manager->pause() : manager->start());
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        plateauManager.removeLeftDirection();
                        break;
                    case sf::Keyboard::Right:
                        plateauManager.removeRightDirection();
                        break;
                    case sf::Keyboard::Up:
                        plateauManager.removeUpDirection();
                        break;
                    case sf::Keyboard::Down:
                        plateauManager.removeDownDirection();
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseMoved:
                plateauManager.setMousePosition(sf::Vector2f{static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)});
                break;
            default:
                break;
        }
    }
}


void main_loop() {
    std::map<std::string, BlocType<BlocFontType>> blocTypes_ {
        {"faible", {sf::Color{0, 0, 200}, 10}}, 
        {"moyen", {sf::Color{200, 0, 0}, 20}},
        {"resistant", {sf::Color{150, 150, 150}, 50}},
        {"invincible", {sf::Color{0, 0, 0}, 1000000}}
    };
    std::map<std::string, BallType<BallFontType>> ballTypes_ {
        {"classique", {sf::Color{120, 255, 0}, 5, 10}}
    };

    ContainerType grille {};
    grille.fill(blocTypes_.at("invincible"));
    grille.fillLines(blocTypes_.at("faible"), 4, 0, 1, 2, 3);
    grille.fillLines(blocTypes_.at("moyen"), 3, 4, 5, 6);
    grille.fillLines(blocTypes_.at("resistant"), 2, 7, 8);

    RectanglePaddle<PaddleFontType> plateau {sf::Color{255, 127, 0}, std::string{"Ligne"}, {150, 10}};
    PaddleManager<PaddleFontType, PaddleShapeType> plateauManager {&plateau};

    std::vector<BallManager<BallFontType, PaddleFontType, ContainerType, PaddleShapeType>*> ballManagers {};
    std::vector<std::unique_ptr<std::thread>> ballThreads {};

    for (size_t i = 0; i < 3; i++) {
        addNewBall(grille, plateauManager.getPaddle(), ballManagers, ballThreads, ballTypes_.at("classique"));
    }

    bool running = true;
    bool pause = false;
    for (auto manager : ballManagers) if (manager != nullptr) manager->start();
    while(running) {
        triggerEvents(running, pause, plateauManager, ballManagers);
        if (!pause) {
            window->clear(sf::Color{15, 5, 107});
            grille.draw();
            plateauManager.move();
            plateauManager.drawPaddle();
            for (auto manager : ballManagers) {
                if (manager != nullptr) manager->drawBall();
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if (!pause) {
            bool stop = true;
            for (auto& manager : ballManagers) if (manager != nullptr && !manager->isStoped()) stop = false;
            if (stop) {
                running = false;
                std::cout << "Stopping" << std::endl;
            }
        }
    }

    for (auto manager : ballManagers) if (manager != nullptr) manager->stop();
    for (auto& thread : ballThreads) if (thread != nullptr) thread->join();
    
    window->setActive(false);
    std::cout << "Fin Main loop" << std::endl;
}


int main(int argc, char const *argv[]) {
    std::cout << "Start main" << std::endl;

    XInitThreads();
    std::srand(std::time(nullptr));

    if (argc > 1) {
        std::this_thread::sleep_for(std::chrono::seconds(atoi(argv[1])));
        std::srand(std::time(nullptr));
        std::this_thread::sleep_for(std::chrono::seconds(5 - atoi(argv[1])));
    }


    window->setKeyRepeatEnabled(false);
    window->setActive(false);
    
    std::thread mainLoopThread ([] () {main_loop();});
    
    mainLoopThread.join();

    window->close();

    return 0;
}

#include <utility>
#include <cstddef>
#include <cstdlib>
#include <array>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

#include "global.h"
#include "squareBloc.cpp"
#include "blocType.hpp"
#include "blocContainer.hpp"
#include "grid.cpp"
#include "ball.hpp"
#include "ballManager.cpp"

sf::RenderWindow* window = nullptr;

using Grille = Grid<sf::Color, 33, 12, 0, 0, 0, 1>;

void addNewBall(Grille &grille, std::vector<BallManager<sf::Color, Grille>*> &ballManagers, std::vector<std::unique_ptr<std::thread>> &ballThreads, BallType<sf::Color> type) {
    auto ballMana = new BallManager<sf::Color, Grille> {
        *new Ball<sf::Color> {
            type, 
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, 
            [](float r){return sf::Vector2f{2*r, 2*-std::sqrt(1-r*r)};} ((float)(rand()) / (float)(RAND_MAX))
        }, 
        &grille
    };
    ballManagers.push_back(std::move(ballMana));
    std::unique_ptr<std::thread> thPtr = std::make_unique<std::thread>([ballMana] () {ballMana->run();});
    ballThreads.push_back(std::move(thPtr));
}

void main_loop(bool &running) {
    BlocType<sf::Color> faible {sf::Color{0, 0, 200}, 10};
    BlocType<sf::Color> moyen {sf::Color{200, 0, 0}, 20};
    BlocType<sf::Color> resistant {sf::Color{150, 150, 150}, 50};
    BlocType<sf::Color> invincible {sf::Color{0, 0, 0}, 1000000};

    BallType<sf::Color> classique {sf::Color{120, 255, 0}, 5, 10};

    Grille grille {};
    grille.fill(invincible);
    grille.fillLines(faible, 4, 0, 1, 2, 3);
    grille.fillLines(moyen, 3, 4, 5, 6);
    grille.fillLines(resistant, 2, 7, 8);

    std::vector<BallManager<sf::Color, Grille>*> ballManagers {};
    std::vector<std::unique_ptr<std::thread>> ballThreads {};

    for (size_t i = 0; i < 5; i++) {
        addNewBall(grille, ballManagers, ballThreads, classique);
    }
    
    while(running) {
        window->clear(sf::Color{15, 5, 107});
        grille.draw();
        for (auto manager : ballManagers) {
            if (manager != nullptr) manager->drawBall();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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


    window = new sf::RenderWindow{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Casse Brique"};

    bool running = true;
    window->setActive(false);
    std::thread mainLoopThread ([&running] () {main_loop(running);});

    while(running){
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
    }
    
    mainLoopThread.join();

    //window->clear();
    window->close();

    return 0;
}

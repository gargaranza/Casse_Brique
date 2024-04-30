#include <utility>
#include <cstddef>
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

void init() {
    window = new sf::RenderWindow{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Casse Brique"};
}


void main_loop() {
    BlocType<sf::Color> faible {sf::Color{0, 0, 200}, 10};
    BlocType<sf::Color> moyen {sf::Color{200, 0, 0}, 20};
    BlocType<sf::Color> resistant {sf::Color{150, 150, 150}, 50};
    BlocType<sf::Color> invincible {sf::Color{0, 0, 0}, 1000000};

    BallType<sf::Color> classique {sf::Color{120, 255, 0}, 5, 5};

    Grille grille {};
    Ball<sf::Color> ball {classique, {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, {3, -2}};
    BallManager<sf::Color, Grille> manager {ball, &grille};
    
    grille.fill(invincible);
    grille.fillLines(faible, 4, 0, 1, 2, 3);
    grille.fillLines(moyen, 3, 4, 5, 6);
    grille.fillLines(resistant, 2, 7, 8);

    grille.draw();

    std::thread myThread ([&manager] () {manager.run();});

    std::this_thread::sleep_for(std::chrono::seconds(5));

    manager.stop();
    myThread.join();

    std::cout << "Fin Main loop" << std::endl;
}


int main(/*int argc, char const *argv[]*/) {
    std::cout << "Start main" << std::endl;
    init();

    main_loop();

    window->clear();
    window->close();

    return 0;
}


#include "global.h"
#include "mainClass.cpp"

const std::shared_ptr<sf::RenderWindow> window {new sf::RenderWindow{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Casse Brique"}};

void init() {
    XInitThreads();

    window->setKeyRepeatEnabled(false);
    window->clear(sf::Color{15, 5, 107});
    window->setActive(false);

    std::srand(std::time(nullptr));
}


int main() {
    std::cout << "Start main" << std::endl;

    init();

    MainClass mainClass {};
    mainClass.loadGrille("");

    std::unique_ptr<std::thread> mainThread = std::make_unique<std::thread>([&mainClass] () {mainClass.run();});

    mainThread->join();

    window->close();

    return 0;
}

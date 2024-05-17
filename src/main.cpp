
#include "mainClass.cpp"

const std::shared_ptr<sf::RenderWindow> window {new sf::RenderWindow{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Casse Brique"}};

void init() {
    XInitThreads();
    std::srand(std::time(nullptr));

    window->setKeyRepeatEnabled(false);
    window->setActive(false);
}

void main_run() {
    MainClass<sf::Color, SquareBloc<sf::Color>, 33, 12, sf::Color, sf::Color, sf::RectangleShape> mainClass {};
    mainClass.loadGrille("");

    mainClass.run();

    window->close();
}

int main() {
    std::cout << "Start main" << std::endl;

    init();
    main_run();

    std::cout << "End program" << std::endl;
    return 0;
}

#include <utility>
#include <cstddef>
#include <array>
#include <memory>
#include <iostream>
#include <thread>

#include "global.h"
#include "squareBloc.cpp"
#include "blocType.hpp"
#include "blocContainer.hpp"
#include "grid.cpp"
#include "ball.cpp"
#include "ballManager.cpp"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Renderer* pRenderer = nullptr;

using Grille = Grid<Uint32, 33, 12, 0, 0, 0, 1>;

void init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    pWindow = SDL_CreateWindow("Casse Brique", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	win_surf = SDL_GetWindowSurface(pWindow);
}

int myFun(void* data) {
    SDL_Init(SDL_INIT_EVERYTHING);
    static_cast<BallManager<Uint32, Grille>*>(data)->run(3);
    return 0;
}


void main_loop() {
    BlocType<Uint32> faible {SDL_MapRGB(win_surf->format, 0, 0, 200), 10};
    BlocType<Uint32> moyen {SDL_MapRGB(win_surf->format, 200, 0, 0), 20};
    BlocType<Uint32> resistant {SDL_MapRGB(win_surf->format, 150, 150, 150), 50};
    BlocType<Uint32> invincible {SDL_MapRGB(win_surf->format, 0, 0, 0), 1000000};

    BallType<Uint32> classique {SDL_MapRGB(win_surf->format, 120, 255, 0), 5, 5};

    Grille grille {};
    Ball<Uint32> ball {classique, {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30}, {3, -2}};
    BallManager<Uint32, Grille> manager {ball, &grille};
    
    grille.fill(invincible);
    grille.fillLines(faible, 4, 0, 1, 2, 3);
    grille.fillLines(moyen, 3, 4, 5, 6);
    grille.fillLines(resistant, 2, 7, 8);

    grille.draw();

    //myFun(&manager);

    SDL_Thread* thread = SDL_CreateThread(myFun, "Main Loop", &manager);

    SDL_Delay(5000);

    manager.stop();

    int threadReturnValue;
    SDL_WaitThread(thread, &threadReturnValue);

    std::cout << "Fin Main loop" << std::endl;
}


int main(/*int argc, char const *argv[]*/) {
    std::cout << "Start main" << std::endl;
    init();

    main_loop();

    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}

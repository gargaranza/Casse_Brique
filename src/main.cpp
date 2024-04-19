#include <SDL2/SDL.h>
#include <utility>
#include <cstddef>
#include <array>
#include "squareBloc.cpp"
#include "blocType.hpp"
#include "blocContainer.hpp"
#include "grid.cpp"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;


void init() {
    pWindow = SDL_CreateWindow("Casse Brique", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
}

void changeColor() {
    SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 120, 120, 120));
    SDL_UpdateWindowSurface(pWindow);
}

void drawSquare() {
    BlocType<Uint32> faible {SDL_MapRGB(win_surf->format, 0, 0, 200), 10};
    BlocType<Uint32> moyen {SDL_MapRGB(win_surf->format, 200, 0, 0), 20};
    BlocType<Uint32> resistant {SDL_MapRGB(win_surf->format, 150, 150, 150), 50};
    BlocType<Uint32> invincible {SDL_MapRGB(win_surf->format, 0, 0, 0), 1000000};

    Grid<Uint32, 33, 12, 0, 0, 0, 1> grille {win_surf};

    grille.fill(invincible);
    grille.fillColumns(faible, 0);
    grille.fillLines(faible, 4, 0, 1, 2, 3);
    grille.fillLines(moyen, 3, 4, 5, 6);
    grille.fillLines(resistant, 2, 7, 8);

    grille.draw();
    
    SDL_UpdateWindowSurface(pWindow);

    SDL_Delay(5000);
}


int main(/*int argc, char const *argv[]*/) {
    init();

    changeColor();
    drawSquare();


    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}

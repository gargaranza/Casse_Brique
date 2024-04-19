#ifndef BLOCCONTAINER_H
#define BLOCCONTAINER_H

#include <SDL2/SDL.h>

template <typename ContT>
class BlocContainer {
    protected:
        ContT container_;
        SDL_Surface* surface_;

        inline BlocContainer(SDL_Surface* surface): surface_{surface} {};
        inline BlocContainer(ContT container, SDL_Surface* surface): container_{container}, surface_{surface} {};

    public:
        virtual ~BlocContainer() {};

        virtual void draw() const {};
};

#endif //BLOCCONTAINER_H
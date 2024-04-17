#ifndef BALLTYPE
#define BALLTYPE

#include <SDL2/SDL.h>
#include <cstddef>

template <typename FontT>
class BallType {
    private:
        const size_t DEGATS;
        const size_t TAILLE;
        const FontT FONT_BASE;
    
    public:
        BallType() = delete;
        inline BallType(FontT font, size_t taille, size_t degats): DEGATS{degats}, TAILLE{taille}, FONT_BASE{font} {};

        inline size_t getTaille() {return TAILLE;};
        inline size_t getDegats() {return DEGATS;};
        inline FontT getFont() {return FONT_BASE;};
};


#endif //BALLTYPE
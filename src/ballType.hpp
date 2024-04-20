#ifndef BALLTYPE
#define BALLTYPE

#include <SDL2/SDL.h>
#include <cstddef>

template <typename FontT>
class BallType {
    private:
        const size_t DEGATS;
        const size_t RAYON;
        const FontT FONT_BASE;
    
    public:
        BallType() = delete;
        inline BallType(FontT font, size_t rayon, size_t degats): DEGATS{degats}, RAYON{rayon}, FONT_BASE{font} {};

        inline size_t getRayon() const {return RAYON;};
        inline size_t getDegats() const {return DEGATS;};
        inline FontT getFont() const {return FONT_BASE;};
};


#endif //BALLTYPE
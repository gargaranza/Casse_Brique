#ifndef BALLTYPE
#define BALLTYPE

#include <SDL2/SDL.h>
#include <cstddef>

template <typename FontT>
class BallType {
    private:
        const size_t DEGATS;
        const float RAYON;
        const FontT FONT_BASE;
    
    public:
        BallType() = delete;
        inline BallType(FontT font, float rayon, size_t degats): DEGATS{degats}, RAYON{rayon}, FONT_BASE{font} {};

        inline float getRayon() const {return RAYON;};
        inline size_t getDegats() const {return DEGATS;};
        inline FontT getFont() const {return FONT_BASE;};
};


#endif //BALLTYPE
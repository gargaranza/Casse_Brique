#ifndef BLOCTYPE_H
#define BLOCTYPE_H

#include <cstddef>

template <typename FontT>
class BlocType {
    private:
        const size_t PV_MAX;
        const FontT FONT_BASE;
    
    public:
        BlocType() = delete;
        inline BlocType(FontT font, size_t pv): PV_MAX{pv}, FONT_BASE{font} {};

        inline size_t getPV() const {return PV_MAX;};
        inline FontT getFont() const {return FONT_BASE;};

};

#endif //BLOCTYPE_H
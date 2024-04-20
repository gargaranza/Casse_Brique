#ifndef BLOC_H
#define BLOC_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <cassert>

template <typename PosT, typename FormeT, typename FontT, typename TypeT>
class Bloc{
    protected:
        PosT position_;
        FormeT forme_;
        TypeT type_;
        FontT font_;

        size_t PV_;

        Bloc() = delete;

        inline Bloc(PosT position, FormeT forme, TypeT type, FontT font, size_t PV): 
            position_{position}, forme_{forme}, type_{type}, font_{font}, PV_{PV} {};

    public:
        virtual ~Bloc() = default;

        inline bool isBroken() {return PV_ == 0;}
        inline bool takeDamage(size_t dmg) {PV_ = std::max(PV_<1000000 ? PV_ - dmg : PV_, static_cast<size_t>(0)) ; return isBroken();}
        
        inline PosT getPosition() const {return position_;};
        
};

#endif //BLOC_H
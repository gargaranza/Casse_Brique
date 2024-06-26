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

        inline Bloc(PosT position, FormeT forme, TypeT type, FontT font, size_t PV): 
            position_{position}, forme_{forme}, type_{type}, font_{font}, PV_{PV} {};

    public:
        Bloc() = delete;
        virtual ~Bloc() = default;

        inline bool isBroken() const {return PV_ == 0;}
        inline bool takeDamage(size_t dmg) {if (isBroken()) return true ; PV_ = std::max(PV_<1000000 ? static_cast<int>(PV_) - dmg : PV_, static_cast<size_t>(0)) ; return isBroken();}

        virtual const std::vector<PosT> getCornerPoints() const = 0;
        virtual bool isIn(sf::Vector2f vect) const = 0;
        
        inline PosT getPosition() const {return position_;};
        
};

#endif //BLOC_H
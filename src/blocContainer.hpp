#ifndef BLOCCONTAINER_H
#define BLOCCONTAINER_H

#include "global.h"

template <typename ContT>
class BlocContainer {
    protected:
        ContT container_;

        BlocContainer() = default;
        inline BlocContainer(ContT &container): container_{container} {};

    public:
        virtual ~BlocContainer() {};

        virtual void draw() const {};
        template <typename Bloc>
        std::vector<Bloc*> getBlocs() {return std::vector<Bloc*> {};};
};

#endif //BLOCCONTAINER_H
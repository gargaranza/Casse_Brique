#ifndef BALLMANAGER
#define BALLMANAGER

#include <memory>
#include <cstddef>
#include "global.h"
#include "ball.hpp"
#include "blocContainer.hpp"

template <typename FontT, typename ContT>
class BallManager{
    private:
        Ball<FontT> ball_;
        ContT* conteneur_;

        bool running = false;

    
    public:
        inline BallManager(Ball<FontT> &ball, ContT* conteneur): ball_{ball}, conteneur_{conteneur} {};

        void run(size_t delay);
        inline void stop() {running = false;};

};


#endif //BALLMANAGER



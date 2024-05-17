#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <utility>
#include <cstddef>
#include <cstdlib>
#include <array>
#include <vector>
#include <set>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include <type_traits>

#include "global.h"
#include "squareBloc.cpp"
#include "blocType.hpp"
#include "blocContainer.cpp"
#include "grid.cpp"
#include "ball.hpp"
#include "ballManager.cpp"
#include "paddle.cpp"
#include "rectanglePaddle.hpp"
#include "paddleManager.cpp"


template <typename BlocFontT, typename BlocT, size_t dim1, size_t dim2, typename BallFontT, typename PaddleFontT, typename PaddleShapeT>
class MainClass {
    private:

        std::map<std::string, BlocType<BlocFontT>> blocTypes_;
        std::map<std::string, BallType<BallFontT>> ballTypes_;

        std::shared_ptr<BlocContainer<dim1, dim2, BlocT, BlocFontT>> container_;
        std::shared_ptr<Paddle<PaddleFontT, PaddleShapeT>> paddle_;

        PaddleManager<PaddleFontT, PaddleShapeT> paddleManager_;

        std::vector<std::shared_ptr<BallManager<BallFontT, PaddleFontT, BlocContainer<dim1, dim2, BlocT, BlocFontT>, PaddleShapeT>>> ballManagers_;
        std::vector<std::unique_ptr<std::thread>> ballThreads_;


        bool running_;
        bool pause_;


        void addNewBall(const BallType<BallFontT> type);
        void triggerEvents();

    public:
        MainClass();

        void loadGrille(const std::string fileName);
        void run();

};



#endif //MAINCLASS_H
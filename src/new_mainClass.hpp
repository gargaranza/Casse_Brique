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

using BlocFontType = sf::Color;
using BlocT = SquareBloc<BlocFontType>;
using BallFontType = sf::Color;
using PaddleFontType = sf::Color;
using PaddleShapeType = sf::RectangleShape;
const size_t dim1 = 33;
const size_t dim2 = 12;
using Grille = Grid<BlocFontType, dim1, dim2, 0, 0, 0, 1>;


class MainClass {
    private:
        std::map<std::string, BlocType<BlocFontType>> blocTypes_;
        std::map<std::string, BallType<BallFontType>> ballTypes_;

        std::shared_ptr<BlocContainer<dim1, dim2, BlocT, BlocFontType>> container_;
        std::shared_ptr<Paddle<PaddleFontType, PaddleShapeType>> paddle_;

        PaddleManager<PaddleFontType, PaddleShapeType> paddleManager_;

        std::vector<std::shared_ptr<BallManager<BallFontType, PaddleFontType, BlocContainer<dim1, dim2, BlocT, BlocFontType>, PaddleShapeType>>> ballManagers_;
        std::vector<std::unique_ptr<std::thread>> ballThreads_;


        bool running_;


        void addNewBall(const BallType<BallFontType> type);
        void triggerEvents();

    public:
        MainClass();

        void loadGrille(const std::string fileName);
        void run();

};



#endif //MAINCLASS_H
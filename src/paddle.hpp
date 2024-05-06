#ifndef PADDLE_H
#define PADDLE_H

#include <functional>
#include <cmath>
#include "global.h"

template <typename FontT, typename ShapeT>
class Paddle {
    protected:
        FontT font_;
        ShapeT paddle_;
        
        sf::Vector2f centerPosition_;
        sf::Vector2f celerite_;

        const std::function<sf::Vector2f(float)> courbe_;

        std::function<sf::Vector2f(float)> getCurve(std::string nom){
            if(nom == "Ligne") {
                return [&] (float x) {return sf::Vector2f{paddle_.getSize().x / 2 * x + (1-x) * (WINDOW_WIDTH - paddle_.getSize().x / 2), WINDOW_HEIGHT - 30};};
            } else {
                return [&] (float x) {return sf::Vector2f{x*0 + WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30};};
            }
        };
        float distance(sf::Vector2f p1, sf::Vector2f p2) {sf::Vector2f v {p2-p1} ; return std::sqrt(v.x * v.x + v.y * v.y);};

        void setPaddlePosition() {paddle_.setPosition(centerPosition_ - paddle_.getSize() / static_cast<float>(2));};

    public:
        inline Paddle(FontT font, ShapeT shape, std::string nomCourbe): 
            font_{font}, paddle_{shape}, centerPosition_{WINDOW_WIDTH/2, WINDOW_HEIGHT - 30}, celerite_{0,0}, courbe_{getCurve(nomCourbe)}
        {
            paddle_.setFillColor(font_);
            setPaddlePosition();
        };

        void updatePosition(sf::Vector2f pos);

        inline const sf::Vector2f getPosition() const {return centerPosition_;};
        inline const sf::Vector2f getSpeed() const {return celerite_;};

        virtual const std::vector<sf::Vector2f> getCornerPoints() const {return std::vector<sf::Vector2f> {};};
        virtual bool isIn(sf::Vector2f vect) {return vect == sf::Vector2f{};};

        inline void draw() {window->draw(paddle_); window->display();};

        //virtual ~Paddle() = 0;
};


#endif //PADDLE_H
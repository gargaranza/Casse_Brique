#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <X11/Xlib.h>
#include <memory>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

extern const std::shared_ptr<sf::RenderWindow> window;

#endif //GLOBAL_H

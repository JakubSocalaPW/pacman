#include "KeyboardController.h"
#include "SFML/Window.hpp"

bool KeyboardController::isArrowDownPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}

bool KeyboardController::isArrowLeftPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
}

bool KeyboardController::isArrowRightPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
}

bool KeyboardController::isArrowUpPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
}

#include "Window.h"

#include <iostream>


void Window::render(Level level) {
    std::cout << "Render refresh \n";
    window.clear(sf::Color::Black);

    drawWalls();
    drawPickables();
    drawPlayers();
    drawScoreboard();
    window.display();
    const std::optional event = window.pollEvent();

}

const std::optional<sf::Event> Window::pollEvents() {
    return window.pollEvent();
}

void Window::drawWalls() {

}

void Window::drawPickables() {

}

void Window::drawPlayers() {

}

void Window::drawScoreboard() {

}

void Window::loadFont() {
    if (!font.openFromFile("C:/Users/jakub/CLionProjects/pacman/Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

bool Window::isOpen() {
    return window.isOpen();
}

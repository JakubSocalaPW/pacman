
#include "Window.h"

#include <iostream>


void Window::render(Level level) {
    std::cout << "Render refresh \n";
    window.clear(sf::Color::Black);

    drawWalls(level.getWallPositions());
    drawPickables();
    drawPlayers();
    drawScoreboard();
    window.display();
}

const std::optional<sf::Event> Window::pollEvents() {
    return window.pollEvent();
}

void Window::drawWalls(std::list<sf::Vector2<int>> positions) {
    sf::RectangleShape rectWall(sf::Vector2f(40.0f, 40.0f));
    rectWall.setFillColor(sf::Color::White);

    for (const auto &a: positions) {
        rectWall.setPosition((sf::Vector2f) a);
        window.draw(rectWall);

    }
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

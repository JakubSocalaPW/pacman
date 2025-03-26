
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "../core/Level.h"

class Window {
    sf::RenderWindow window;
    const int MAX_FRAMERATE = 60;
    const sf::Color PACMAN_COLOR;
    const sf::Color GHOST_COLOR;
    const sf::Color WALL_COLOR;
    const sf::Color DOT_COLOR;
    const sf::Color POWERUP_COLOR;
    sf::Font font;

    void loadFont();
    void drawWalls(std::list<sf::Vector2<int>>);
    void drawPickables();
    void drawPlayers();
    void drawScoreboard();

public:
    Window()
        : PACMAN_COLOR(255, 255, 0),
          GHOST_COLOR(255, 0, 0),
          WALL_COLOR(0, 0, 255),
          DOT_COLOR(255, 255, 255),
          POWERUP_COLOR(255, 255, 255),
          window(sf::VideoMode({800, 800}), "Multiplayer PacMan") {
        loadFont();
        window.setFramerateLimit(MAX_FRAMERATE); // todo move to window.cpp
    }
    void render(Level level);
    bool isOpen();
    const std::optional<sf::Event> pollEvents();
};



#endif //WINDOW_H

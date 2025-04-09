
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "../../common/level//Level.h"
#include "../core/Scoreboard.h"

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
    void drawObjectives(std::list<Objective> objectives);
    void drawPowerUps(std::list<PowerUp> powerUps);
    void drawPlayers(std::vector<PlayerCharacter*>& players);
    void drawScoreboard(Scoreboard& scoreboard);

public:
    Window();
    void render(Level& level, Scoreboard& scoreboard);
    bool isOpen();
    bool hasFocus();
    void close();
    const std::optional<sf::Event> pollEvents();
};



#endif //WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <optional>
#include "../../common/level/Level.h"
#include "../core/Scoreboard.h"
#include "../../common/abstract/PlayerCharacter.h"

class Window {
public:
    Window();
    void render(Level& level, Scoreboard& scoreboard);
    std::optional<sf::Event> pollEvents();
    bool isOpen();
    bool hasFocus();
    void close();
    void resize() {
        // Get the new size of the window
        sf::Vector2u windowSize = window.getSize();

        // Resize the default view to match the new window size
        sf::View view = window.getDefaultView();
        view.setSize({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
        // Set the center of the view to (0, 0) so the game starts from the top-left
        view.setCenter({0.f, 0.f});  // Top-left corner of the game world

        // Apply the new view to the window
        window.setView(view);
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Color PACMAN_COLOR;
    sf::Color GHOST_COLOR;
    sf::Color WALL_COLOR;
    sf::Color DOT_COLOR;
    sf::Color POWERUP_COLOR;

    void drawWalls(std::list<sf::Vector2<int>> positions, float tileSize, float offsetX, float offsetY);
    void drawObjectives(std::list<Objective> objectives, float tileSize, float offsetX, float offsetY);
    void drawPowerUps(std::list<PowerUp> powerUps, float tileSize, float offsetX, float offsetY);
    void drawPlayers(std::vector<PlayerCharacter*>& players, float tileSize, float offsetX, float offsetY);
    void drawScoreboard(Scoreboard& scoreboard, float scoreboardWidth);
    void loadFont();

};

#endif // WINDOW_H

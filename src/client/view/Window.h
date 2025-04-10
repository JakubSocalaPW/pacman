#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <optional>
#include "../../common/level/Level.h"
#include "../core/Scoreboard.h"
#include "../../common/abstract/PlayerCharacter.h"

/**
 * @class Window
 *
 * A class responsible for managing the game window and rendering game elements.
 *
 * This class encapsulates the SFML RenderWindow and provides methods to draw
 * different game components like the level, players, objectives, and the scoreboard.
 */
class Window {
private:
    sf::RenderWindow _window;
    sf::Font _font;

    //todo move colors to Drawable class
    sf::Color PACMAN_COLOR;
    sf::Color GHOST_COLOR;
    sf::Color WALL_COLOR;
    sf::Color DOT_COLOR;
    sf::Color POWERUP_COLOR;

    void _drawWalls(std::list<sf::Vector2<int>> positions, float tileSize);
    void _drawObjectives(std::list<Objective> objectives, float tileSize);
    void _drawPowerUps(std::list<PowerUp> powerUps, float tileSize);
    void _drawPlayers(std::vector<PlayerCharacter*>& players, float tileSize);
    void _drawScoreboard(Scoreboard& scoreboard, float scoreboardWidth);
    void _loadFont();

public:
    /**
     * @brief Constructor for the Window class.
     *
     * Initializes the render window, loads the font, and sets the default colors.
     */
    Window();

    /**
     * @brief Renders the current state of the game level and scoreboard on the window.
     * @param level A reference to the Level object to draw.
     * @param scoreboard A reference to the Scoreboard object to draw.
     */
    void render(Level& level, Scoreboard& scoreboard);

    /**
     * @brief Polls for pending SFML events (e.g., keyboard input, window close).
     * @return An optional sf::Event object if an event occurred.
     */
    std::optional<sf::Event> pollEvents();

    /**
     * @brief Checks if the window is currently open.
     * @return True if the window is open, false otherwise.
     */
    bool isOpen();

    /**
     * @brief Checks if the window currently has focus.
     * @return True if the window has focus, false otherwise.
     */
    bool hasFocus();

    /**
     * @brief Closes the game window.
     */
    void close();
};

#endif // WINDOW_H
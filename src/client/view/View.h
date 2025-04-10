#ifndef VIEW_H
#define VIEW_H

#include "Window.h"
#include "../core/Scoreboard.h"
#include "../../common/level/Level.h"

/**
 * @class View
 * @brief Controller for windows.
 *
 * This class provides methods to draw the game level, the scoreboard, and
 * to manage the window display. Responsible for rendering the game state on the window.
 */
class View {
private:
    Window _window;

public:
    /**
     * @brief Draws the current state of the game (level and the scoreboard) on the window.
     * @param level A reference to the Level object containing the game map and entities.
     * @param scoreboard A reference to the Scoreboard object containing player scores and game information.
     */
    void drawLevel(Level& level, Scoreboard& scoreboard);

    /**
     * @brief Refreshes the window to display the currently drawn elements, by polling for events.
     * @return True if the window was successfully refreshed, false otherwise (e.g., if the window is closed).
     */
    bool refreshWindow();

    /**
     * @brief Checks if the window currently has focus.
     * @return True if the window has focus, false otherwise.
     */
    bool hasFocus();
};

#endif //VIEW_H
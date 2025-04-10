#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

/**
 * @class KeyboardController
 * A static class that provides methods to check the state of arrow keys.
 *
 * This class offers static functions to easily determine if the up, down, left,
 * or right arrow keys are currently being pressed.
 * It is base input controller for the game.
 */
class KeyboardController {
public:
    /**
     * @brief Checks if the up arrow key is currently pressed.
     * @return True if the up arrow key is pressed, false otherwise.
     */
    static bool isArrowUpPressed();

    /**
     * @brief Checks if the down arrow key is currently pressed.
     * @return True if the down arrow key is pressed, false otherwise.
     */
    static bool isArrowDownPressed();

    /**
     * @brief Checks if the left arrow key is currently pressed.
     * @return True if the left arrow key is pressed, false otherwise.
     */
    static bool isArrowLeftPressed();

    /**
     * @brief Checks if the right arrow key is currently pressed.
     * @return True if the right arrow key is pressed, false otherwise.
     */
    static bool isArrowRightPressed();
};

#endif //KEYBOARDCONTROLLER_H

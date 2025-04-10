#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>

#include "../../common/level/Level.h"

/**
 * @brief A class responsible for generating and managing game levels.
 *
 * This class holds a collection of predefined game level templates and provides
 * functionality to access the current level and advance to the next one.
 * It also handles the initialization of player characters within each level.
 */
class LevelGenerator {
private:
    int _index = 0;
    std::vector<Level> _generatedLevels;

    std::vector<std::vector<int>> _firstLevel = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
        {1, 3, 1, 1, 1, 2, 1, 2, 1, 1, 1, 3, 1},
        {1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1},
        {1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
        {1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> _secondLevel = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
        {1, 3, 2, 2, 1, 2, 2, 2, 1, 2, 2, 3, 1},
        {1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
        {1, 2, 1, 1, 3, 2, 1, 2, 3, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
        {1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> _thirdLevel = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
        {1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1},
        {1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1},
        {1, 2, 1, 2, 1, 1, 3, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
        {1, 3, 1, 1, 1, 2, 1, 2, 1, 1, 1, 3, 1},
        {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
        {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> _fourthLevel = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 3, 2, 2, 2, 2, 2, 3, 2, 2, 1},
        {1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 2, 2, 3, 2, 2, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 3, 2, 1, 2, 3, 1, 1, 2, 1},
        {1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1},
        {1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1},
        {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
        {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    std::vector<std::vector<int>> _fifthLevel = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 1, 2, 2, 3, 2, 2, 1, 2, 2, 1},
        {1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 3, 1, 2, 1, 2, 1, 3, 1, 2, 1},
        {1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1},
        {1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1},
        {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
        {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

public:
    /**
     * @brief Constructor for the LevelGenerator class.
     *
     * Initializes the level generator by loading the predefined game levels.
     */
    LevelGenerator();

    /**
     * @brief Gets a reference to the currently active game level.
     * @return A reference to the Level object at the current index.
     */
    Level& getCurrentLevel();

    /**
     * @brief Gets the total number of levels managed by the generator.
     * @return The total number of generated levels.
     */
    int getTotalGeneratedLevels() const;

    /**
     * @brief Advances to the next level in the sequence.
     *
     * If the current level is the last one, it resets to the first level.
     * It also handles the creation and assignment of player characters
     * (Pac-Man and Ghosts) for the new level, ensuring one Pac-Man and
     * the rest as Ghosts.
     */
    void nextLevel();
};
#endif //LEVELGENERATOR_H
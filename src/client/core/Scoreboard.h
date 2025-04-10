#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>
#include <chrono>
#include "../../common/player/Player.h"

/**
 * @class Scoreboard
 * Manages the game scoreboard, tracking players, objectives, and game log.
 *
 * Container for everything needed to display the scoreboard in the game.
 */
class Scoreboard {
private:
    std::vector<Player*> _players;
    int _objectivesLeft = 0;
    std::chrono::steady_clock::time_point _creationTime;
    std::vector<std::string> _logEntries;

public:
    /**
     * @brief Default constructor for the Scoreboard class.
     *
     * Initializes the creation time of the scoreboard.
     */
    Scoreboard();

    /**
     * @brief Clears all players from the scoreboard.
     *
     * This function removes all player pointers from the internal vector. Note that
     * this does not deallocate the Player objects themselves.
     */
    void clearPlayers();

    /**
     * @brief Adds a player to the scoreboard.
     * @param player A pointer to the Player object to be added.
     */
    void addPlayer(Player* player);

    /**
     * @brief Sets the number of objectives left in the game.
     * @param objectivesLeft The new number of objectives remaining.
     */
    void setObjectivesLeft(int objectivesLeft);

    /**
     * @brief Adds an entry to the game log.
     * @tparam T The type of the entry to be added. This will be converted to a string.
     * @param entry The entry to add to the log.
     *
     * This is a template method allowing various data types to be added to the log.
     * The entry will be converted to its string representation before being stored.
     */
    template<typename T>
        void addToLog(const T& entry) {
        if constexpr (std::is_arithmetic_v<T>) {
            _logEntries.push_back(std::to_string(entry));
        } else if constexpr (std::is_same_v<T, std::string>) {
            _logEntries.push_back(entry);
        } else if constexpr (std::is_same_v<T, const char*>) {
            _logEntries.push_back(std::string(entry));
        } else {
            static_assert(sizeof(T) == 0, "Unsupported type for addToLog");
        }
    }

    /**
     * @brief Retrieves the game log entries.
     * @return A vector of strings representing the log entries.
     */
    std::vector<std::string> getLogs() const;


    /**
     * @brief Gets the number of objectives left in the game.
     * @return The number of objectives remaining.
     */
    int getObjectivesLeft() const;

    /**
     * @brief Retrieves the scores of all players currently on the scoreboard.
     * @return A vector of strings, where each string represents a player's score
     * (e.g., "PlayerName: 123").
     */
    std::vector<std::string> getPlayersScores();

    /**
     * @brief Calculates the elapsed time in seconds since the scoreboard was created.
     * @return A double representing the elapsed time in seconds.
     */
    double getElapsedTimeSeconds() const;
};

#endif //SCOREBOARD_H
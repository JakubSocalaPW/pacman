#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include "../../common/player/Player.h"

class Scoreboard {
private:
    std::vector<Player*> _players;
    int _objectivesLeft = 0;
    std::chrono::steady_clock::time_point _creationTime;
    std::vector<std::string> _logEntries;

public:
    Scoreboard() {
        _creationTime = std::chrono::steady_clock::now();
    }
    // void updateScore(const std::string& playerName, int score);
    // std::vector<int> getScores() const;
    // void addLogEntry(const std::string& entry);
    void clearPlayers() {
        _players.clear();
    }
    void addPlayer(Player* player) {
        _players.push_back(player);
    }

    void setObjectivesLeft(int objectivesLeft) {
        _objectivesLeft = objectivesLeft;
    }

    template<typename T>
    void addToLog(const T& entry) {
        _logEntries.push_back(std::to_string(entry));
    }

    int getObjectivesLeft() const {
        return _objectivesLeft;
    }

    std::vector<std::string> getPlayersScores() {
        std::vector<std::string> scores;
        for (const auto& player : _players) {
            std::cout << "Player: " << player << std::endl;
            scores.push_back(player->getNickname() + ": " + std::to_string(player->getScore()));
        }
        return scores;
    }

    double getElapsedTimeSeconds() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - _creationTime;
        return elapsed.count();
    }
};


#endif //SCOREBOARD_H

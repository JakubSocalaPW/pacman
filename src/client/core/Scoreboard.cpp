#include "Scoreboard.h"

Scoreboard::Scoreboard() {
    _creationTime = std::chrono::steady_clock::now();
}

void Scoreboard::clearPlayers() {
    _players.clear();
}

void Scoreboard::addPlayer(Player* player) {
    _players.push_back(player);
}

void Scoreboard::setObjectivesLeft(int objectivesLeft) {
    _objectivesLeft = objectivesLeft;
}

template<typename T>
void Scoreboard::addToLog(const T& entry) {
    _logEntries.push_back(std::to_string(entry));
}

int Scoreboard::getObjectivesLeft() const {
    return _objectivesLeft;
}

std::vector<std::string> Scoreboard::getPlayersScores() {
    std::vector<std::string> scores;
    for (const auto& player : _players) {
        scores.push_back(player->getNickname() + ": " + std::to_string(player->getScore()));
    }
    return scores;
}

double Scoreboard::getElapsedTimeSeconds() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - _creationTime;
    return elapsed.count();
}
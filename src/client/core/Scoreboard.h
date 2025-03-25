#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>

class Scoreboard {
private:
    std::vector<std::string> m_logs;
    std::vector<int> m_scores;

public:
    void updateScore(const std::string& playerName, int score);
    std::vector<int> getScores() const;
    void addLogEntry(const std::string& entry);
};


#endif //SCOREBOARD_H

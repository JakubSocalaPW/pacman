
#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H


#include "../../client/core/Level.h"

class LevelGenerator {
private:
    int m_index;
    std::vector<Level> m_generatedLevels;

public:
    LevelGenerator();
    Level generateLevel(int difficulty);
    Level getCurrentLevel();
    int getTotalGeneratedLevels() const;
};
#endif //LEVELGENERATOR_H

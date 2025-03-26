
#include "LevelGenerator.h"


LevelGenerator::LevelGenerator() {
    m_generatedLevels.push_back(Level(firstLevel));
    m_generatedLevels.push_back(Level(secondLevel));
    m_generatedLevels.push_back(Level(thirdLevel));
    m_generatedLevels.push_back(Level(fourthLevel));
    m_generatedLevels.push_back(Level(fifthLevel));
    m_index = 0;
}

Level LevelGenerator::getCurrentLevel() {
    return m_generatedLevels[m_index];
}

int LevelGenerator::getTotalGeneratedLevels() const {
    return m_generatedLevels.size();
}




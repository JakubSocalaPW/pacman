
#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H


#include <iostream>

#include "../../common/level/Level.h"

class LevelGenerator {
private:
    int m_index;
    std::vector<Level> m_generatedLevels;

    std::vector<std::vector<int>> firstLevel = {
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

std::vector<std::vector<int>> secondLevel = {
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

std::vector<std::vector<int>> thirdLevel = {
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

std::vector<std::vector<int>> fourthLevel = {
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

std::vector<std::vector<int>> fifthLevel = {
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
    LevelGenerator();
    Level& getCurrentLevel();
    int getTotalGeneratedLevels() const;
    void nextLevel() {
        std::cout << "LevelGenerator::nextLevel()" << std::endl;

        if ( (m_index + 1) % m_generatedLevels.size() == 0) {
            std::vector<PlayerCharacter*> newCharacters;
            bool foundNewPacMan = false;
            // Then create new character objects
            for (size_t i = 0; i < getCurrentLevel().getPlayerCharacters().size(); i++) {
                auto* currentPlayer = getCurrentLevel().getPlayerCharacters()[i];
                Player* playerPtr = &currentPlayer->getPlayer();

                bool shouldBePacManNow = false;

                if (!currentPlayer->isPacman() && !foundNewPacMan) {
                    shouldBePacManNow = true;
                    foundNewPacMan = true;
                }


                if (shouldBePacManNow) {
                    newCharacters.push_back(new PacMan(1, 1, playerPtr));
                } else {
                    newCharacters.push_back(new Ghost(1, 1, playerPtr));
                }



            }
            m_generatedLevels.clear();
            m_generatedLevels.push_back(Level(firstLevel));
            m_generatedLevels.push_back(Level(secondLevel));
            m_generatedLevels.push_back(Level(thirdLevel));
            m_generatedLevels.push_back(Level(fourthLevel));
            m_generatedLevels.push_back(Level(fifthLevel));
            m_index = 0;
            // Finally, replace the original collection
            getCurrentLevel().setPlayerCharacters(newCharacters);
        }
        else {
            std::vector<PlayerCharacter*> newCharacters;

            //add players to level todo split player and playuer character
            int index = 1;
            for (auto& player : getCurrentLevel().getPlayerCharacters()) {
                Player* playerptr = &player->getPlayer();
                PlayerCharacter* newPlayer;
                if ( player->isPacman()) {
                    newPlayer =  new PacMan(1 + (index * 2), 1, playerptr);
                }
                else {
                    newPlayer =  new Ghost(1 + (index * 2), 1, playerptr);
                }


                index++;
                newCharacters.push_back(newPlayer);
            }

            for (auto &player: getCurrentLevel().getPlayerCharacters()) {
                delete player;
                player = nullptr;
            }

            m_index = (m_index + 1) % m_generatedLevels.size();
            m_generatedLevels[m_index].setPlayerCharacters(newCharacters);

        }

    }
};
#endif //LEVELGENERATOR_H

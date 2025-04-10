#include "LevelGenerator.h"
#include "../../common/player/PacMan.h"

LevelGenerator::LevelGenerator() {
    _generatedLevels.push_back(Level(_firstLevel));
    _generatedLevels.push_back(Level(_secondLevel));
    _generatedLevels.push_back(Level(_thirdLevel));
    _generatedLevels.push_back(Level(_fourthLevel));
    _generatedLevels.push_back(Level(_fifthLevel));
    _index = 0;
}

Level &LevelGenerator::getCurrentLevel() {
    return _generatedLevels[_index];
}

int LevelGenerator::getTotalGeneratedLevels() const {
    return _generatedLevels.size();
}

void LevelGenerator::nextLevel() {
    if ((_index + 1) % _generatedLevels.size() == 0) {
        std::vector<PlayerCharacter *> newCharacters;
        bool foundNewPacMan = false;

        for (size_t i = 0; i < getCurrentLevel().getPlayerCharacters().size(); i++) {
            auto *currentPlayer = getCurrentLevel().getPlayerCharacters()[i];
            Player *playerPtr = &currentPlayer->getPlayer();
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

        _generatedLevels.clear();
        _generatedLevels.push_back(Level(_firstLevel));
        _generatedLevels.push_back(Level(_secondLevel));
        _generatedLevels.push_back(Level(_thirdLevel));
        _generatedLevels.push_back(Level(_fourthLevel));
        _generatedLevels.push_back(Level(_fifthLevel));
        _index = 0;

        // Finally, replace the original collection

        getCurrentLevel().setPlayerCharacters(newCharacters);
    } else {
        std::vector<PlayerCharacter *> newCharacters;


        int index = 1;

        for (auto &player: getCurrentLevel().getPlayerCharacters()) {
            Player *playerptr = &player->getPlayer();

            PlayerCharacter *newPlayer;

            if (player->isPacman()) {
                newPlayer = new PacMan(1 + (index * 2), 1, playerptr);
            } else {
                newPlayer = new Ghost(1 + (index * 2), 1, playerptr);
            }


            index++;
            newCharacters.push_back(newPlayer);
        }

        for (auto &player: getCurrentLevel().getPlayerCharacters()) {
            delete player;

            player = nullptr;
        }

        _index = (_index + 1) % _generatedLevels.size();
        _generatedLevels[_index].setPlayerCharacters(newCharacters);
    }
}

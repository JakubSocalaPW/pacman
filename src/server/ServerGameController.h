
#ifndef SERVERGAMECONTROLLER_H
#define SERVERGAMECONTROLLER_H

#include <map>
#include <vector>
#include "../client/core/PlayerCharacter.h"


class ServerGameController {
private:
    std::vector<PlayerCharacter> m_players;
    bool m_isGameActive;

public:
    void startGame();
    void detectCollisions();
    void broadcastUpdatedState();
    void handlePlayerMovement(int playerId, int direction);
};


#endif //SERVERGAMECONTROLLER_H

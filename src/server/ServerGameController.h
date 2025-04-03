#ifndef SERVERGAMECONTROLLER_H
#define SERVERGAMECONTROLLER_H

#include "network/NetworkHost.h"


class PlayerCharacter;

class ServerGameController {
private:
    // std::vector<PlayerCharacter> m_players;
    bool m_isGameActive;
    NetworkHost networkHost;
    LevelGenerator levelGenerator;
    void detectCollisions();

    void handlePlayerMovement(int playerId, int direction);

public:
    ServerGameController();
    void broadcastUpdatedState();
    void startGame();
    Level& getCurrentLevel();
    void addPlayer(const std::string& name);
    void movePlayer(const std::string& name, int direction);
    void removePlayer(const std::string& name);
};


#endif //SERVERGAMECONTROLLER_H

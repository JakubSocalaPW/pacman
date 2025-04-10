#include "Window.h"

#include <iostream>

#include "../core/Scoreboard.h"


Window::Window()
    : PACMAN_COLOR(sf::Color::Yellow),
      GHOST_COLOR(sf::Color::Red),
      WALL_COLOR(sf::Color::Blue),
      DOT_COLOR(sf::Color::White),
      POWERUP_COLOR(sf::Color::White),
      _window(sf::VideoMode({800, 600}), "Online PacMan") {
    _loadFont();

    _window.setFramerateLimit(60);
}


void Window::render(Level &level, Scoreboard &scoreboard) {
    _window.clear(sf::Color::Black);

    float tileWidth = 800 / level.getSize(); // Assuming grid size of 13x13
    float tileHeight = 600 / level.getSize(); // Assuming grid size of 12x12
    float tileSize = std::min(tileWidth, tileHeight); // Keep the tile size consisten

    _drawWalls(level.getWallPositions(), tileSize);
    _drawObjectives(level.getObjectives(), tileSize);
    _drawPowerUps(level.getPowerUps(), tileSize);
    _drawPlayers(level.getPlayerCharacters(), tileSize);
    _drawScoreboard(scoreboard, 240.0f);

    _window.display();
}


std::optional<sf::Event> Window::pollEvents() {
    return _window.pollEvent();
}


void Window::_drawWalls(std::list<sf::Vector2<int> > positions, float tileSize) {
    sf::RectangleShape rectWall(sf::Vector2f(tileSize, tileSize));
    rectWall.setFillColor(WALL_COLOR);

    for (const auto &position: positions) {
        rectWall.setPosition({position.x * tileSize, position.y * tileSize});
        _window.draw(rectWall);
    }
}


void Window::_drawObjectives(std::list<Objective> objectives, float tileSize) {
    float dotRadius = tileSize * 0.1f;
    sf::CircleShape objectiveShape(dotRadius);
    objectiveShape.setFillColor(DOT_COLOR);

    for (const auto &objective: objectives) {
        objectiveShape.setPosition({
            objective.getPosition().x * tileSize + tileSize / 2 - dotRadius,

            objective.getPosition().y * tileSize + tileSize / 2 - dotRadius
        });

        _window.draw(objectiveShape);
    }
}


void Window::_drawPowerUps(std::list<PowerUp> powerUps, float tileSize) {
    float powerUpRadius = tileSize * 0.15f;

    sf::CircleShape powerUpShape(powerUpRadius);

    for (const auto &powerUp: powerUps) {
        const auto currentColor = powerUp.getType() == PowerUpType::SpeedBoost
                                      ? sf::Color(157, 172, 255)
                                      : powerUp.getType() == PowerUpType::Invincibility
                                            ? sf::Color(40, 75, 99)
                                            : powerUp.getType() == PowerUpType::GhostKiller
                                                  ? sf::Color(135, 92, 116)
                                                  : sf::Color(65, 234, 212);

        powerUpShape.setFillColor(currentColor);
        powerUpShape.setPosition({
            powerUp.getPosition().x * tileSize + tileSize / 2 - powerUpRadius,
            powerUp.getPosition().y * tileSize + tileSize / 2 - powerUpRadius
        });
        _window.draw(powerUpShape);
    }
}


void Window::_drawPlayers(std::vector<PlayerCharacter *> &players, float tileSize) {
    float playerRadius = tileSize * 0.4f;

    sf::CircleShape playerShape(playerRadius);
    sf::Text nicknameText(_font);

    nicknameText.setCharacterSize(static_cast<unsigned int>(tileSize * 0.3f));
    nicknameText.setFillColor(sf::Color::White);

    for (auto player: players) {
        if (player == nullptr) continue;

        playerShape.setFillColor(player->isPacman()
                                     ? (player->getIsInvincible()
                                            ? sf::Color(169, 134, 0)
                                            : (player->getIsGhostKiller()
                                                   ? sf::Color(255, 200, 100)
                                                   : PACMAN_COLOR))
                                     : GHOST_COLOR);

        playerShape.setPosition({
            player->getPosition().x * tileSize + tileSize / 2 - playerRadius,
            player->getPosition().y * tileSize + tileSize / 2 - playerRadius
        });

        _window.draw(playerShape);


        // Draw nickname above player
        nicknameText.setString(player->getPlayer().getNickname());
        sf::FloatRect textBounds = nicknameText.getLocalBounds();
        nicknameText.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.0f, textBounds.position.y + textBounds.size.y
        });

        nicknameText.setPosition({
            player->getPosition().x * tileSize + tileSize / 2,
            player->getPosition().y * tileSize - tileSize * 0.1f
        });

        _window.draw(nicknameText);
    }
}


void Window::_drawScoreboard(Scoreboard &scoreboard, float scoreboardWidth) {
    sf::RectangleShape scoreboardPanel(sf::Vector2f(scoreboardWidth, 600));
    scoreboardPanel.setPosition({800 - scoreboardWidth, 0});
    scoreboardPanel.setFillColor(sf::Color(50, 50, 50, 200));

    _window.draw(scoreboardPanel);

    float startX = 800 - scoreboardWidth + 20.0f;
    float currentY = 20.0f;
    float lineHeight = 25.0f;


    // Scoreboard title

    sf::Text headerText(_font);

    headerText.setString("SCOREBOARD");
    headerText.setCharacterSize(28);
    headerText.setStyle(sf::Text::Bold);
    headerText.setFillColor(sf::Color::White);
    headerText.setPosition({
        startX + (scoreboardWidth - 40.0f) / 2.0f - headerText.getLocalBounds().size.x / 2.0f, currentY
    });

    _window.draw(headerText);

    currentY += 40.0f;


    // Divider line
    sf::RectangleShape divider(sf::Vector2f(scoreboardWidth - 40.0f, 2.0f));
    divider.setPosition({startX, currentY});
    divider.setFillColor(sf::Color::White);
    _window.draw(divider);

    currentY += 20.0f;


    // Display player scores
    sf::Text scoreText(_font);
    scoreText.setCharacterSize(20);
    std::vector<std::string> playerScores = scoreboard.getPlayersScores();

    for (const auto &score: playerScores) {
        sf::CircleShape playerIcon(8.0f);

        playerIcon.setFillColor(sf::Color::Yellow); //todo set color based on player type
        playerIcon.setPosition({startX + 10.0f, currentY + 5.0f});
        _window.draw(playerIcon);

        scoreText.setString(score);
        scoreText.setPosition({startX + 30.0f, currentY});
        _window.draw(scoreText);

        currentY += lineHeight;
    }

    currentY += 15.0f;

    divider.setPosition({startX, currentY});
    _window.draw(divider);

    currentY += 20.0f;

    // Game info section
    sf::Text gameInfoTitle(_font);
    gameInfoTitle.setString("Game Info");
    gameInfoTitle.setCharacterSize(22);
    gameInfoTitle.setStyle(sf::Text::Bold);
    gameInfoTitle.setFillColor(sf::Color::White);
    gameInfoTitle.setPosition({startX, currentY});
    _window.draw(gameInfoTitle);

    currentY += 30.0f;


    sf::Text gameInfoText(_font);
    gameInfoText.setCharacterSize(18);
    gameInfoText.setFillColor(sf::Color::White);
    gameInfoText.setString("Objectives Left: " + std::to_string(scoreboard.getObjectivesLeft()));
    gameInfoText.setPosition({startX, currentY});

    _window.draw(gameInfoText);

    currentY += lineHeight;

    gameInfoText.setString("Time: " + std::to_string(static_cast<int>(scoreboard.getElapsedTimeSeconds())) + "s");
    gameInfoText.setPosition({startX, currentY});
    _window.draw(gameInfoText);

    currentY += lineHeight;


    currentY += 15.0f;

    divider.setPosition({startX, currentY});
    _window.draw(divider);

    currentY += 15.0f;

    for (const auto &log: scoreboard.getLogs()) {

        scoreText.setString(log);
        scoreText.setCharacterSize(12);
        scoreText.setPosition({startX, currentY});
        _window.draw(scoreText);

        currentY += lineHeight;
    }
}


void Window::_loadFont() {
    if (!_font.openFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}


bool Window::isOpen() {
    return _window.isOpen();
}


bool Window::hasFocus() {
    return _window.hasFocus();
}


void Window::close() {
    _window.close();
}

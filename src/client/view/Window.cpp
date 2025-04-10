#include "Window.h"

#include <iostream>

#include "../core/Scoreboard.h"


Window::Window()

    : PACMAN_COLOR(sf::Color::Yellow),

      GHOST_COLOR(sf::Color::Red),

      WALL_COLOR(sf::Color::Blue),

      DOT_COLOR(sf::Color::White),

      POWERUP_COLOR(sf::Color::White),

      window(sf::VideoMode({800, 600}), "Multiplayer PacMan") {
    loadFont();

    window.setFramerateLimit(60);
}


void Window::render(Level &level, Scoreboard &scoreboard) {
    window.clear(sf::Color::Black);


    sf::Vector2u windowSize = window.getSize(); // Get the current window size

    // float baseWidth = 800.0f; // Base resolution width (e.g., 800x600)
    //
    // float baseHeight = 600.0f; // Base resolution height
    //
    //
    // // Calculate scale factors based on the window size
    //
    // float scaleX = static_cast<float>(windowSize.x) / baseWidth;
    //
    // float scaleY = static_cast<float>(windowSize.y) / baseHeight;
    //
    // float scale = std::min(scaleX, scaleY); // Use the smallest scale factor to preserve aspect ratio
    //

    float tileWidth = 800 / level.getSize(); // Assuming grid size of 13x13

    float tileHeight = 600 / level.getSize(); // Assuming grid size of 12x12

    float tileSize = std::min(tileWidth, tileHeight); // Keep the tile size consisten


    // Draw game elements with the scaled tile size and offset

    drawWalls(level.getWallPositions(), tileSize, 0, 0);

    drawObjectives(level.getObjectives(), tileSize, 0, 0);

    drawPowerUps(level.getPowerUps(), tileSize, 0, 0);

    drawPlayers(level.getPlayerCharacters(), tileSize, 0, 0);

    drawScoreboard(scoreboard, 240.0f);


    window.display();
}


std::optional<sf::Event> Window::pollEvents() {
    return window.pollEvent();
}


void Window::drawWalls(std::list<sf::Vector2<int> > positions, float tileSize, float offsetX, float offsetY) {
    sf::RectangleShape rectWall(sf::Vector2f(tileSize, tileSize));

    rectWall.setFillColor(WALL_COLOR);

    for (const auto &position: positions) {
        rectWall.setPosition({position.x * tileSize + offsetX, position.y * tileSize + offsetY});

        window.draw(rectWall);
    }
}


void Window::drawObjectives(std::list<Objective> objectives, float tileSize, float offsetX, float offsetY) {
    float dotRadius = tileSize * 0.1f;

    sf::CircleShape objectiveShape(dotRadius);

    objectiveShape.setFillColor(DOT_COLOR);

    for (const auto &objective: objectives) {
        objectiveShape.setPosition({
            objective.getPosition().x * tileSize + offsetX + tileSize / 2 - dotRadius,

            objective.getPosition().y * tileSize + offsetY + tileSize / 2 - dotRadius
        });

        window.draw(objectiveShape);
    }
}


void Window::drawPowerUps(std::list<PowerUp> powerUps, float tileSize, float offsetX, float offsetY) {
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
            powerUp.getPosition().x * tileSize + offsetX + tileSize / 2 - powerUpRadius,

            powerUp.getPosition().y * tileSize + offsetY + tileSize / 2 - powerUpRadius
        });

        window.draw(powerUpShape);
    }
}


void Window::drawPlayers(std::vector<PlayerCharacter *> &players, float tileSize, float offsetX, float offsetY) {
    float playerRadius = tileSize * 0.4f;

    sf::CircleShape playerShape(playerRadius);

    sf::Text nicknameText(font);

    nicknameText.setCharacterSize(static_cast<unsigned int>(tileSize * 0.3f));

    nicknameText.setFillColor(sf::Color::White);


    std::cout << "Drawing players: " << std::to_string(players.size()) << std::endl;

    for (auto player: players) {
        if (player == nullptr) continue;

        std::cout << "Drawing player: " << std::endl;

        playerShape.setFillColor(player->isPacman()

                                     ? (player->getIsInvincible()
                                            ? sf::Color(169, 134, 0)

                                            : (player->getIsGhostKiller()

                                                   ? sf::Color(255, 200, 100)

                                                   : PACMAN_COLOR))

                                     : GHOST_COLOR);

        playerShape.setPosition({
            player->getPosition().x * tileSize + offsetX + tileSize / 2 - playerRadius,

            player->getPosition().y * tileSize + offsetY + tileSize / 2 - playerRadius
        });

        window.draw(playerShape);


        // Draw nickname above player

        nicknameText.setString(player->getPlayer().getNickname());

        sf::FloatRect textBounds = nicknameText.getLocalBounds();

        nicknameText.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.0f, textBounds.position.y + textBounds.size.y
        });

        nicknameText.setPosition({
            player->getPosition().x * tileSize + offsetX + tileSize / 2,

            player->getPosition().y * tileSize + offsetY - tileSize * 0.1f
        });

        window.draw(nicknameText);
    }
}


void Window::drawScoreboard(Scoreboard &scoreboard, float scoreboardWidth) {
    sf::Vector2u windowSize = window.getSize();

    sf::RectangleShape scoreboardPanel(sf::Vector2f(scoreboardWidth, 600));

    scoreboardPanel.setPosition({800 - scoreboardWidth, 0});

    scoreboardPanel.setFillColor(sf::Color(50, 50, 50, 200));

    window.draw(scoreboardPanel);


    float startX = 800 - scoreboardWidth + 20.0f;

    float currentY = 20.0f;

    float lineHeight = 25.0f;


    // Scoreboard title

    sf::Text headerText(font);

    headerText.setString("SCOREBOARD");

    headerText.setCharacterSize(28);

    headerText.setStyle(sf::Text::Bold);

    headerText.setFillColor(sf::Color::White);

    headerText.setPosition({
        startX + (scoreboardWidth - 40.0f) / 2.0f - headerText.getLocalBounds().size.x / 2.0f, currentY
    });

    window.draw(headerText);

    currentY += 40.0f;


    // Divider line

    sf::RectangleShape divider(sf::Vector2f(scoreboardWidth - 40.0f, 2.0f));

    divider.setPosition({startX, currentY});

    divider.setFillColor(sf::Color::White);

    window.draw(divider);

    currentY += 20.0f;


    // Display player scores

    sf::Text scoreText(font);

    scoreText.setCharacterSize(20);

    std::vector<std::string> playerScores = scoreboard.getPlayersScores();

    for (const auto &score: playerScores) {
        // Player icon (you might want to associate colors with players)

        sf::CircleShape playerIcon(8.0f);

        playerIcon.setFillColor(sf::Color::Cyan); // Placeholder color

        playerIcon.setPosition({startX + 10.0f, currentY + 5.0f});

        window.draw(playerIcon);


        scoreText.setString(score);

        scoreText.setPosition({startX + 30.0f, currentY});

        window.draw(scoreText);

        currentY += lineHeight;
    }


    currentY += 15.0f;

    divider.setPosition({startX, currentY});

    window.draw(divider);

    currentY += 20.0f;


    // Game info section

    sf::Text gameInfoTitle(font);

    gameInfoTitle.setString("Game Info");

    gameInfoTitle.setCharacterSize(22);

    gameInfoTitle.setStyle(sf::Text::Bold);

    gameInfoTitle.setFillColor(sf::Color::White);

    gameInfoTitle.setPosition({startX, currentY});

    window.draw(gameInfoTitle);

    currentY += 30.0f;


    sf::Text gameInfoText(font);

    gameInfoText.setCharacterSize(18);

    gameInfoText.setFillColor(sf::Color::White);

    gameInfoText.setString("Objectives Left: " + std::to_string(scoreboard.getObjectivesLeft()));

    gameInfoText.setPosition({startX, currentY});

    window.draw(gameInfoText);

    currentY += lineHeight;


    gameInfoText.setString("Time: " + std::to_string(static_cast<int>(scoreboard.getElapsedTimeSeconds())) + "s");

    gameInfoText.setPosition({startX, currentY});

    window.draw(gameInfoText);
}


void Window::loadFont() {
    if (!font.openFromFile("C:/Users/jakub/CLionProjects/pacman/Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}


bool Window::isOpen() {
    return window.isOpen();
}


bool Window::hasFocus() {
    return window.hasFocus();
}


void Window::close() {
    window.close();
}

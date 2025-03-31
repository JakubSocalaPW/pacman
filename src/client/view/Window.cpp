
#include "Window.h"

#include <iostream>


void Window::render(Level level) {
    window.clear(sf::Color::Black);

    drawWalls(level.getWallPositions());
    drawObjectives(level.getObjectives());
    drawPowerUps(level.getPowerUps());
    drawPlayers(level.getPlayers());
    drawScoreboard(level.getPlayers()); //todo pass scoreboard here
    window.display();
}

const std::optional<sf::Event> Window::pollEvents() {
    return window.pollEvent();
}

void Window::drawWalls(std::list<sf::Vector2<int>> positions) {
    sf::RectangleShape rectWall(sf::Vector2f(40.0f, 40.0f));
    rectWall.setFillColor(sf::Color::White);
    for (const auto &position: positions) {
        rectWall.setPosition({position.x * 40.0f, position.y * 40.0f});
        window.draw(rectWall);
    }
}

void Window::drawObjectives(std::list<Objective> objectives) {
    sf::CircleShape objectiveShape(5.0f);
    objectiveShape.setFillColor(sf::Color::Green);
    for (const auto &objective:  objectives){
        objectiveShape.setPosition({objective.getPosition().x * 40.0f + 15.0f, objective.getPosition().y * 40.0f + 15.0f});
        window.draw(objectiveShape);
    }
}

void Window::drawPowerUps(std::list<PowerUp> powerUps) {
    sf::CircleShape powerUpShape(7.0f);
    powerUpShape.setFillColor(sf::Color::Yellow);
    for (const auto &powerUp: powerUps) {
        powerUpShape.setPosition({powerUp.getPosition().x * 40.0f + 15.0f, powerUp.getPosition().y * 40.0f + 15.0f});
        window.draw(powerUpShape);
    }
}


void Window::drawPlayers(std::vector<Player> players) {
    sf::CircleShape playerShape(10.0f);
    for (const auto &player: players) {
        playerShape.setFillColor(player.getIsPacman() ? PACMAN_COLOR : GHOST_COLOR);
        playerShape.setPosition({player.getPosition().x * 40.0f + 15.0f, player.getPosition().y * 40.0f + 15.0f});
        window.draw(playerShape);
    }
}

void Window::drawScoreboard(std::vector<Player> players) {
     if (font.getInfo().family.empty()) {
        loadFont();
    }

    // Get window size for positioning the scoreboard
    sf::Vector2u windowSize = window.getSize();

    // Create a background panel for the scoreboard
    sf::RectangleShape scoreboardPanel;
    float panelWidth = 200.0f;
    float panelHeight = windowSize.y;
    scoreboardPanel.setSize(sf::Vector2f(panelWidth, panelHeight));
    scoreboardPanel.setPosition({windowSize.x - panelWidth, 0});
    scoreboardPanel.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent dark gray
    window.draw(scoreboardPanel);

    // Create "SCOREBOARD" header
    sf::Text headerText(font);
    headerText.setFont(font);
    headerText.setString("SCOREBOARD");
    headerText.setCharacterSize(28);
    headerText.setStyle(sf::Text::Bold);
    headerText.setFillColor(sf::Color::White);

    // Center the header text in the panel
    float headerX = windowSize.x - panelWidth + (panelWidth - headerText.getLocalBounds().size.x) / 2;
    headerText.setPosition({headerX, 20.0f});
    window.draw(headerText);

    // Horizontal line below header
    sf::RectangleShape divider;
    divider.setSize(sf::Vector2f(panelWidth - 40.0f, 2.0f));
    divider.setPosition({windowSize.x - panelWidth + 20.0f, 60.0f});
    divider.setFillColor(sf::Color::White);
    window.draw(divider);

    // Player scores
    sf::Text scoreText(font);
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    float startY = 80.0f;

    // For each player in players (you'll need to store or pass this)
    for (size_t i = 0; i < players.size(); i++) {
        Player& player = players[i];

        // Player icon
        sf::CircleShape playerIcon(10.0f);
        playerIcon.setFillColor(player.getIsPacman() ? PACMAN_COLOR : GHOST_COLOR);
        playerIcon.setPosition({windowSize.x - panelWidth + 30.0f, startY + 5.0f});
        window.draw(playerIcon);

        // Set text color based on player type
        scoreText.setFillColor(sf::Color::White);

        // Create player label
        std::string playerLabel = player.getIsPacman() ? ("P " + player.getNickname()) : ("G " + player.getNickname()) + std::to_string(i);
        scoreText.setString(playerLabel);
        scoreText.setPosition({windowSize.x - panelWidth + 60.0f, startY});
        window.draw(scoreText);

        // Create score display
        std::string scoreStr = std::to_string(player.getPosition().x) + ", " + std::to_string(player.getPosition().y);
        scoreText.setString(scoreStr);
        scoreText.setPosition({windowSize.x - 60.0f, startY});
        window.draw(scoreText);

        // Increment Y position for next player's score
        startY += 40.0f;
    }

    // Additional game information
    startY += 20.0f;
    divider.setPosition({windowSize.x - panelWidth + 20.0f, startY});
    window.draw(divider);

    startY += 20.0f;
    scoreText.setCharacterSize(20);
    scoreText.setString("Game Info");
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition({windowSize.x - panelWidth + 30.0f, startY});
    window.draw(scoreText);

    startY += 30.0f;
    scoreText.setStyle(sf::Text::Regular);
    scoreText.setCharacterSize(18);
    scoreText.setString("Objectives Left: " + std::to_string(0)); // todo replace with actual objectives left
    scoreText.setPosition({windowSize.x - panelWidth + 30.0f, startY});
    window.draw(scoreText);

    startY += 25.0f;
    scoreText.setString("Time: " + std::to_string(0) + "s"); //todo add
    scoreText.setPosition({windowSize.x - panelWidth + 30.0f, startY});
    window.draw(scoreText);
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

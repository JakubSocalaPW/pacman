#include "View.h"

#include "../core/Scoreboard.h"

bool View::refreshWindow() {
    while (const std::optional event = _window.pollEvents()) {
        if (event->is<sf::Event::Closed>()) {
            _window.close();
            return false;
        }
        if (event->is<sf::Event::Resized>()) {
        }
    }
    return true;
}

void View::drawLevel(Level& level, Scoreboard& scoreboard) {
    _window.render(level, scoreboard);
}

bool View::hasFocus() {
    return _window.hasFocus();
}

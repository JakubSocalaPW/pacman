#include "View.h"

bool View::refreshWindow() {
    while (const std::optional event = window.pollEvents()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return false;
        }
    }
    return true;
}

void View::drawLevel(const Level& level) {
    window.render(level);
}

bool View::hasFocus() {
    return window.hasFocus();
}

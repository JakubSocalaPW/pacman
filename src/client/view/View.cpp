#include "View.h"

bool View::refreshWindow() {
    while (const std::optional event = _window.pollEvents()) {
        if (event->is<sf::Event::Closed>()) {
            _window.close();
            return false;
        }
    }
     return true;
}

void View::drawLevel(Level& level) {
    _window.render(level);
}

bool View::hasFocus() {
    return _window.hasFocus();
}

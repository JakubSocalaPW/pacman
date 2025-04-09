
#ifndef VIEW_H
#define VIEW_H
#include "Window.h"
#include "../core/Scoreboard.h"


class View {
    Window _window;
public:
    void drawLevel(Level& level, Scoreboard& scoreboard);
    void drawScoreboard();
    bool refreshWindow();
    bool hasFocus();
};


#endif //VIEW_H

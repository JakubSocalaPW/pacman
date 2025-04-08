
#ifndef VIEW_H
#define VIEW_H
#include "Window.h"


class View {
    Window _window;
public:
    void drawLevel(Level& level);
    void drawScoreboard();
    bool refreshWindow();
    bool hasFocus();
};


#endif //VIEW_H

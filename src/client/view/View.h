
#ifndef VIEW_H
#define VIEW_H
#include "Window.h"


class View {
    Window window;
public:
    void drawLevel(const Level& level);
    void drawScoreboard();
    bool refreshWindow();
    bool hasFocus();
};


#endif //VIEW_H

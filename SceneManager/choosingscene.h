#ifndef CHOOSINGSCENE_H
#define CHOOSINGSCENE_H

#include "scene.h"

class ChoosingScene : public Scene
{
public:
    ChoosingScene(QPainter* widget_painter);
    ~ChoosingScene();

    void on_enter();
    void on_update(int delta);
    void on_draw();
    void on_input();
    void on_exit();
};

#endif // CHOOSINGSCENE_H

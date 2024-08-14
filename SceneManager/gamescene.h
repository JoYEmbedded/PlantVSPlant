#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "scene.h"
#include <QDebug>

class GameScene : public Scene
{
public:
    GameScene(QPainter* widget_painter);
    ~GameScene();

    void on_enter();
    void on_update(int delta);
    void on_draw();
    void on_input();
    void on_exit();

};

#endif // GAMESCENE_H

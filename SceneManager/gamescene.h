#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "scene.h"
#include <QDebug>

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void on_enter();
    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input();
    void on_exit();

};

#endif // GAMESCENE_H

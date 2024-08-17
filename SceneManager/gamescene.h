#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "scene.h"
#include <QDebug>
#include "scenemanager.h"

extern SceneManager* scene_manager;

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

private:
    // bool eventFilter(QObject* obj, QEvent* event);
};

#endif // GAMESCENE_H

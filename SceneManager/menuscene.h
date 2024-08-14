#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "scene.h"
#include <QDebug>
#include "scenemanager.h"
#include "animation.h"

extern Atlas atlas_peashooter_run_right;
extern SceneManager* scene_manager;

class MenuScene : public Scene
{
public:
    MenuScene(QPainter* widget_painter);
    ~MenuScene() = default;

    void on_enter();
    void on_update(int delta);
    void on_draw();
    void on_input();
    void on_exit();

private:
    bool eventFilter(QObject* obj, QEvent* event);
    Animation animation_peashooter_run_right;
};

#endif // MENUSCENE_H

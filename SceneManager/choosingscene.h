#ifndef CHOOSINGSCENE_H
#define CHOOSINGSCENE_H

#include "scene.h"
#include "scenemanager.h"
extern SceneManager* scene_manager;
class ChoosingScene : public Scene
{
public:
    ChoosingScene();
    ~ChoosingScene();

    void on_enter();
    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input();
    void on_exit();

private:
    // bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CHOOSINGSCENE_H

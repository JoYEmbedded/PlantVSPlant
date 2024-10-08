#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "scene.h"
#include <QDebug>
#include "scenemanager.h"
#include "MY_DEF.h"
#include "./graphics/animation.h"
#include "timer.h"

extern QImage img_menu_background;
extern Atlas atlas_peashooter_run_right;

extern MusicPlayer* music_bgm_menu;
extern MusicPlayer* music_ui_confirm;

extern SceneManager* scene_manager;


class MenuScene : public Scene
{
public:
    MenuScene();
    ~MenuScene() = default;

    void on_enter();
    void on_update(int delta, Camera& camera);
    void on_draw(QPainter* widget_painter, const Camera& camera);
    void on_input(QKeyEvent* event, KeyType key_type);
    void on_exit();
    void paint(QPainter* widget_painter);

private:
    // bool eventFilter(QObject* obj, QEvent* event);
    Animation animation_peashooter_run_right;
    Timer timer;
};

#endif // MENUSCENE_H

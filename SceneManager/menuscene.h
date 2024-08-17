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

extern QMediaPlayer music_bgm_menu;
extern QMediaPlayer music_ui_confirm;
extern QAudioOutput* music_audio_output;

extern SceneManager* scene_manager;


class MenuScene : public Scene
{
public:
    MenuScene();
    ~MenuScene() = default;

    void on_enter();
    void on_update(int delta);
    void on_draw(QPainter* widget_painter, const Camera& camera);
    void on_input();
    void on_exit();
    void paint(QPainter* widget_painter);

private:
    // bool eventFilter(QObject* obj, QEvent* event);
    Animation animation_peashooter_run_right;
    Timer timer;
};

#endif // MENUSCENE_H

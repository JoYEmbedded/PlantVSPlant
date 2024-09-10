#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "scene.h"
#include <QDebug>
#include "scenemanager.h"
#include "MY_DEF.h"
#include "platform.h"
#include "Players/peashootplayer.h"
#include "Players/sunflowerplayer.h"
#include "statusbar.h"
extern QImage img_sky;
extern QImage img_hills;
extern QImage img_platform_large;
extern QImage img_platform_small;

extern MusicPlayer* music_bgm_game;

extern Player* player_1;
extern Player* player_2;
extern QImage* img_player_1_avatar;
extern QImage* img_player_2_avatar;
extern SceneManager* scene_manager;

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void on_enter();
    void on_update(int delta, Camera& camera);
    void on_draw(QPainter* widget_painter, const Camera& camera);
    void on_input(QKeyEvent* event, KeyType key_type);
    void on_exit();
    void move_and_collision(int delta);

private:
    // bool eventFilter(QObject* obj, QEvent* event);

    QPoint pos_img_sky = {0,0};
    QPoint pos_img_hills = {0,0};
    std::vector<Platform> platform_list;
    StatusBar status_bar_1P;
    StatusBar status_bar_2P;

    const float gravity = 1.6e-3f;
};

#endif // GAMESCENE_H

#ifndef SUNFLOWERPLAYER_H
#define SUNFLOWERPLAYER_H
#include "player.h"
#include <QPainter>
#include "Bullet/sunbullet.h"
#include "Bullet/sunbulletex.h"

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;

extern Player* player_1;
extern Player* player_2;

extern MusicPlayer* music_sun_text;

class SunflowerPlayer : public Player
{
public:
    SunflowerPlayer();
    ~SunflowerPlayer();

    void on_update(int delta, Camera& camera);
    void on_draw(QPainter* widget_painter, const Camera& my_camera);
    void on_input(QKeyEvent* event, KeyType key_type);
    void on_attack();
    void on_attack_ex();
private:
    const float speed_sun_ex = 0.15f;
    const QVector2D velocity_sun = { 0.25f, -0.5f};             //小型日光炸弹抛射速度

    Animation animation_sun_text;
    bool is_sun_text_visible = false;
};

#endif // SUNFLOWERPLAYER_H

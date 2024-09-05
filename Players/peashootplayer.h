#ifndef PEASHOOTPLAYER_H
#define PEASHOOTPLAYER_H
#include "player.h"
#include "Bullet/peabullet.h"
#include <QDebug>

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_left;
extern Atlas atlas_peashooter_attack_ex_right;

extern QMediaPlayer music_pea_shoot_1;
extern QMediaPlayer music_pea_shoot_2;
extern QMediaPlayer music_pea_shoot_ex;
extern QAudioOutput* music_audio_output;

class PeashootPlayer : public Player
{
public:
    PeashootPlayer();
    ~PeashootPlayer();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input(QKeyEvent* event, KeyType key_type);

    void on_attack();
    void on_attack_ex();
private:
    void spawn_pea_bullet(float speed);

    const float speed_pea = 0.75f;
    const float speed_pea_ex = 1.5f;
    const int attack_ex_duration = 2500;//特殊攻击状态持续时长

    Timer timer_attack_ex;              //特殊攻击状态定时器
    Timer timer_spawn_pea_ex;           //豌豆子弹发射定时器
};

#endif // PEASHOOTPLAYER_H

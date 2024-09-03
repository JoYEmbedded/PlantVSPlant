#ifndef PEABULLET_H
#define PEABULLET_H
#include "bullet.h"
#include <QMediaPlayer>
#include "graphics/animation.h"

extern QMediaPlayer music_pea_break_1;
extern QMediaPlayer music_pea_break_2;
extern QMediaPlayer music_pea_break_3;
extern QAudioOutput* music_audio_output;

extern Atlas atlas_pea_break;
extern QImage img_pea;

class PeaBullet : public Bullet
{
public:
    PeaBullet();
    void on_collide();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter, const Camera& camera);

private:
    Animation animation_break;
};

#endif // PEABULLET_H

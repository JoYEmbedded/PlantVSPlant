#ifndef SUNBULLETEX_H
#define SUNBULLETEX_H
#include "bullet.h"
#include "graphics/animation.h"
#include <QMediaPlayer>
#include "camera.h"
extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;

extern QMediaPlayer music_sun_explode_ex;
extern QAudioOutput* music_audio_output;

class SunBulletEx : public Bullet
{
public:
    SunBulletEx();
    ~SunBulletEx();

    void on_collide();
    void on_update(int delta);
    void on_draw(QPainter* widget_painter, const Camera& camera);

    bool check_collision(const QVector2D& other_position, const QVector2D& other_size);

private:
    Animation animation_idle;
    Animation animation_explode;
    QVector2D explode_render_offset;
};

#endif // SUNBULLETEX_H

#ifndef SUNBULLET_H
#define SUNBULLET_H
#include "bullet.h"
#include <QMediaPlayer>
#include "graphics/animation.h"

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;
extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Atlas atlas_sun_text;

extern QMediaPlayer music_sun_explode;;
extern QAudioOutput* music_audio_output;

class SunBullet : public Bullet
{
public:
    SunBullet();
    ~SunBullet();

    void on_collide();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter, const Camera& camera);
private:
    Animation animation_idle;       //日光炸弹默认动画
    Animation animation_explode;    //日光炸弹爆炸动画
    QVector2D explode_render_offset;//爆炸渲染偏移
    const float gravity = 1e-3f;
};

#endif // SUNBULLET_H
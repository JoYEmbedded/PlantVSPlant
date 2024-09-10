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

extern MusicPlayer* music_sun_explode;;

class SunBullet : public Bullet
{
public:
    SunBullet();
    ~SunBullet();

    void on_collide();

    void on_update(int delta, Camera& camera);
    void on_draw(QPainter* widget_painter, const Camera& camera);
private:
    Animation animation_idle;       //日光炸弹默认动画
    Animation animation_explode;    //日光炸弹爆炸动画
    QVector2D explode_render_offset;//爆炸渲染偏移
    const float gravity = 1e-3f;
};

#endif // SUNBULLET_H

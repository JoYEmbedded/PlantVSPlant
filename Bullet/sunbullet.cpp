#include "sunbullet.h"

SunBullet::SunBullet()
{
    size.setX(96);
    size.setY(96);
    damage = 20;
    animation_idle.set_atlas(&atlas_sun);
    animation_idle.set_interval(50);
    animation_idle.set_loop(true);

    animation_explode.set_atlas(&atlas_sun_explode);
    animation_explode.set_interval(50);
    animation_explode.set_loop(false);
    animation_explode.set_callback([&](){can_be_removed = true;});
    QImage frame_idle = animation_idle.get_frame();
    QImage frame_explode = animation_explode.get_frame();
    explode_render_offset.setX((frame_explode.width()-frame_idle.width()) / 2.0f);
    explode_render_offset.setY((frame_explode.height() - frame_idle.height()) / 2.0f);

}

void SunBullet::on_collide()
{
    Bullet::on_collide();
    music_sun_explode->play();
}

void SunBullet::on_update(int delta, Camera& camera)
{
    if(valid)
    {
        velocity.setY( velocity.y() + gravity * delta);
        position += velocity * (float)delta;
        animation_idle.on_update(delta);
    }
    else
    {
        animation_explode.on_update(delta);
    }
}

void SunBullet::on_draw(QPainter* widget_painter, const Camera& camera)
{
    if(valid)
    {
        animation_idle.on_draw(position.x(), position.y(), widget_painter);
    }
    else
    {
        animation_explode.on_draw(position.x() - explode_render_offset.x(), position.y() - explode_render_offset.y(), widget_painter);
    }
}

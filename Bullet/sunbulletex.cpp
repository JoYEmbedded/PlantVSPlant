#include "sunbulletex.h"

SunBulletEx::SunBulletEx()
{
    size.setX(288);
    size.setY(288);

    damage = 20;
    animation_idle.set_atlas(&atlas_sun_ex);
    animation_idle.set_interval(50);
    animation_idle.set_loop(true);

}

void SunBulletEx::on_collide()
{
    Bullet::on_collide();
    music_sun_explode_ex.setAudioOutput(music_audio_output);
    music_sun_explode_ex.play();

}

void SunBulletEx::on_update(int delta)
{
    if(valid)
    {
        position += velocity * (float)delta;
        animation_idle.on_update(delta);
    }
    else
    {
        animation_explode.on_update(delta);
    }
    if (check_if_exceed_screen())
        can_be_removed = true;
}

bool SunBulletEx::check_collision(const QVector2D& other_position, const QVector2D& other_size)
{
    bool is_collision_x = std::max(position.x() + size.x(), other_position.x() + other_size.x()) - std::min<int>(position.x(), other_position.x())
                          <= size.x() + other_size.x();
    bool is_collision_y = std::max(position.y() + size.y(), other_position.y() + other_size.y()) - std::min<int>(position.y(), other_position.y())
                          <= size.y() + other_size.y();
    return is_collision_x && is_collision_y;
}

void SunBulletEx::on_draw(QPainter* widget_painter, const Camera& camera)
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

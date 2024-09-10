#include "sunbulletex.h"

SunBulletEx::SunBulletEx()
{
    size.setX(288);
    size.setY(288);

    damage = 20;
    animation_idle.set_atlas(&atlas_sun_ex);
    animation_idle.set_interval(50);
    animation_idle.set_loop(true);

    animation_explode.set_atlas(&atlas_sun_ex_explode);
    animation_explode.set_interval(75);
    animation_explode.set_loop(false);
    animation_explode.set_callback([&](){can_be_removed = true;});
}

void SunBulletEx::on_collide()
{
    Bullet::on_collide();
    music_sun_explode_ex->play();

}

void SunBulletEx::on_update(int delta, Camera& camera)
{
    if(valid)
    {
        position += velocity * (float)delta;
        animation_idle.on_update(delta);
    }
    else
    {
        animation_explode.on_update(delta);
        camera.shake(20, 25);   //duration小于20不正常
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
    QVector2D pos_camera = camera.get_position();
    if(valid)
    {
        animation_idle.on_draw(position.x() + pos_camera.x(), position.y() + pos_camera.y(), widget_painter);
    }
    else
    {
        animation_explode.on_draw(position.x() - explode_render_offset.x() + pos_camera.x(), position.y() - explode_render_offset.y() + pos_camera.y(), widget_painter);
    }
}

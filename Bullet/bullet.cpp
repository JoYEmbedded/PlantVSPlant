#include "bullet.h"

Bullet::Bullet() {}

Bullet::~Bullet(){}

void Bullet::set_damage(int new_damage)
{
    damage = new_damage;
}

int Bullet::get_damage() const
{
    return damage;
}

void Bullet::set_position(float x, float y)
{
    position.setX(x);
    position.setY(y);
}

const QVector2D& Bullet::get_position() const
{
    return position;
}

const QVector2D& Bullet::get_size()
{
    return size;
}

void Bullet::set_velocity(float x, float y)
{
    velocity.setX(x);
    velocity.setY(y);
}

void Bullet::set_collide_target(PlayerID player_id)
{
    target_ID = player_id;
}

PlayerID Bullet::get_collide_target() const
{
    return target_ID;
}

void Bullet::set_callback(std::function<void()> callback)
{
    this->callback = callback;
}

void Bullet::set_valid(bool flag)
{
    valid = flag;
}

bool Bullet::get_valid() const
{
    return valid;
}

bool Bullet::check_can_remove() const
{
    return can_be_removed;
}

void Bullet::on_collide()
{
    if(callback)
        callback();
}

bool Bullet::check_collision(const QVector2D& other_position, const QVector2D& other_size)
{
    return position.x() + size.x() / 2 >= other_position.x()
           && position.x() + size.x() / 2 <= other_position.x() + other_size.x()
           && position.y() + size.y() / 2 >= other_position.y()
           && position.y() + size.y() / 2 <= other_position.y() + other_size.y();
}

bool Bullet::check_if_exceed_screen()
{
    return position.x() + size.x() <= 0 || position.x() >= WINDOW_WIDTH || position.y() >= WINDOW_HEIGHT;
}

void Bullet::on_update(int delta, Camera& camera)
{

}

void Bullet::on_draw(QPainter* widget_painter, const Camera& camera)
{

}

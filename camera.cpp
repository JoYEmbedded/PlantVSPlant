#include "camera.h"

Camera::Camera()
{
    timer_shake.set_one_shot(true);
    timer_shake.set_callback(
                   [this]()
                   {
                       is_shaking = false;
                       reset();
        });
    m_position.setX(0);
    m_position.setY(0);
}

const QVector2D Camera::get_position() const
{
    return m_position;
}

void Camera::reset()
{
    m_position.setX(0);
    m_position.setY(0);
}

void Camera::on_update(int delta)
{
    timer_shake.on_update(delta);
    if(is_shaking)
    {
        m_position.setX((-50 + rand()%100)/50.0f * shaking_strength);
        m_position.setY((-50 + rand()%100)/50.0f * shaking_strength);
    }
}

void Camera::shake(float strength, int duration)
{
    shaking_strength = strength;
    timer_shake.set_wait_time(duration);
    is_shaking = true;
    timer_shake.restart();
}

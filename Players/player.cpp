#include "player.h"

Player::Player()
{
    current_animation = &animation_idle_right;

    timer_attack_cd.set_wait_time(attack_cd);
    timer_attack_cd.set_one_shot(true);
    timer_attack_cd.set_callback([&](){can_attack = true;});
}

Player::~Player(){}

void Player::on_update(int delta)
{
    int direction = is_move_right_btn_pressed - is_move_left_btn_pressed;
    if(direction != 0)
    {
        is_facing_right = direction > 0;
        current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
        float distance = run_velocity * delta * direction;
        on_run(distance);
    }
    else
    {
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
    }
    current_animation->on_update(delta);
    timer_attack_cd.on_update(delta);
}

void Player::on_draw(QPainter* widget_painter)
{
    current_animation->on_draw(position.x(), position.y(), widget_painter);
}

void Player::on_input(QKeyEvent* event, KeyType key_type)
{
    if(key_type == KeyType::Press)
    {
        switch (id) {
        case PlayerID::P1:
            switch (event->key()) {
            case Qt::Key_A:
                is_move_left_btn_pressed = true;
                break;
            case Qt::Key_D:
                is_move_right_btn_pressed = true;
                break;

            case Qt::Key_J:
                is_shoot_btn_pressed = true;
                if(can_attack)
                {
                    on_attack();
                    can_attack = false;
                    timer_attack_cd.restart();
                }
                break;

            case Qt::Key_K:
                is_jump_btn_pressed = true;
                on_jump();
                break;

            case Qt::Key_U:
                is_shoot_ex_btn_pressed = true;
                if(MP >= 100)
                {
                    on_attack_ex();
                    MP = 0;
                }
                break;
            }
            break;
        case PlayerID::P2:
            switch (event->key()) {
            case Qt::Key_Left:
                is_move_left_btn_pressed = true;
                break;
            case Qt::Key_Right:
                is_move_right_btn_pressed = true;
                break;

            case Qt::Key_1:
                is_shoot_btn_pressed = true;
                if(can_attack)
                {
                    on_attack();
                    can_attack = false;
                    timer_attack_cd.restart();
                }
                break;

            case Qt::Key_2:
                is_jump_btn_pressed = true;
                on_jump();
                break;

            case Qt::Key_4:
                is_shoot_ex_btn_pressed = true;
                if(MP >= 100)
                {
                    on_attack_ex();
                    MP = 0;
                }
                break;
            }
            break;
        }
    }
    if(key_type == KeyType::Release)
    {
        switch (id) {
        case PlayerID::P1:
            switch (event->key()) {
            case Qt::Key_A:
                is_move_left_btn_pressed = false;
                break;
            case Qt::Key_D:
                is_move_right_btn_pressed = false;
                break;

            case Qt::Key_J:
                is_shoot_btn_pressed = false;
                break;

            case Qt::Key_K:
                is_jump_btn_pressed = false;
                break;

            case Qt::Key_U:
                is_shoot_ex_btn_pressed = false;
                break;
            }
            break;
        case PlayerID::P2:
            switch (event->key()) {
            case Qt::Key_Left:
                is_move_left_btn_pressed = false;
                break;
            case Qt::Key_Right:
                is_move_right_btn_pressed = false;
                break;

            case Qt::Key_1:
                is_shoot_btn_pressed = false;
                break;

            case Qt::Key_2:
                is_jump_btn_pressed = false;
                break;

            case Qt::Key_4:
                is_shoot_ex_btn_pressed = false;
                break;
            }
            break;
        }
    }

}

void Player::set_id(PlayerID id)
{
    this->id = id;
}

void Player::set_position(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void Player::on_run(float distance)
{
    if (is_attacking_ex)
        return;
    this->position.setX(position.x() + distance);
}

QPoint Player::get_position()
{
    return QPoint(position.x(), position.y());
}

QVector2D Player::get_velocity()
{
    return QVector2D(velocity.x(), velocity.y());
}

QVector2D Player::get_shape()
{
    return QVector2D(shape.x(), shape.y());
}

void Player::set_velocity(QVector2D new_velocity)
{
    velocity.setX(new_velocity.x());
    velocity.setY(new_velocity.y());
}

void Player::on_jump()
{
    if(velocity.y() != 0 || is_attacking_ex)
        return;
    velocity.setY(jump_velocity);
}

void Player::on_attack()
{

}

void Player::on_attack_ex()
{

}

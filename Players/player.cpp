#include "player.h"

Player::Player()
{
    current_animation = &animation_idle_right;
}

Player::~Player(){}

void Player::on_update(int delta)
{
    int direction = is_move_right_btn_pressed - is_move_left_btn_pressed;
    if(direction != 0)
    {
        is_facing_right = direction > 0;
        current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
    }
    else
    {
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
    }
    current_animation->on_update(delta);
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
                break;

            case Qt::Key_K:
                is_jump_btn_pressed = true;
                break;

            case Qt::Key_U:
                is_shoot_ex_btn_pressed = true;
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
                break;

            case Qt::Key_2:
                is_jump_btn_pressed = true;
                break;

            case Qt::Key_4:
                is_shoot_ex_btn_pressed = true;
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

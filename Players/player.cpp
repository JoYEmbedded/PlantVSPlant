#include "player.h"

Player::Player(bool facing_right) : is_facing_right(facing_right)
{
    current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

    animation_jump_effect.set_atlas(&atlas_jump_effect);
    animation_jump_effect.set_interval(25);
    animation_jump_effect.set_loop(false);
    animation_jump_effect.set_callback([&]()
                                       {
                             is_jump_effect_visible = false;
    });

    animation_land_effect.set_atlas(&atlas_land_effect);
    animation_land_effect.set_interval(50);
    animation_land_effect.set_loop(false);
    animation_land_effect.set_callback([&]()
                                       {
                             is_land_effect_visible = false;
    });

    timer_attack_cd.set_wait_time(attack_cd);
    timer_attack_cd.set_one_shot(true);
    timer_attack_cd.set_callback([&](){can_attack = true;});

    timer_invulnerable.set_wait_time(invulnerable_time);
    timer_invulnerable.set_one_shot(true);
    timer_invulnerable.set_callback([&](){is_invulnerable = false;});

    timer_invulnerable_blink.set_wait_time(75);
    timer_invulnerable_blink.set_one_shot(false);
    timer_invulnerable_blink.set_callback([&](){is_showing_sketch_frame = !is_showing_sketch_frame;});

    timer_run_effect_generation.set_wait_time(75);
    timer_run_effect_generation.set_callback(
        [&]()
        {
            QVector2D particle_position;
            QImage frame = atlas_run_effect.get_img(0);
            particle_position.setX(position.x() + (shape.x() - frame.width()) / 2);
            particle_position.setY(position.y() +(shape.y() - frame.height()));
            particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
        });
    timer_run_effect_generation.set_one_shot(false);
    timer_die_effect_generation.set_wait_time(35);
    timer_die_effect_generation.set_callback(
        [&]()
        {
            QVector2D particle_position;
            QImage frame = atlas_run_effect.get_img(0);
            particle_position.setX(position.x() + (shape.x() - frame.width()) / 2);
            particle_position.setY(position.y() + shape.y() - frame.height());
            particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
        });

    timer_cursor_visibility.set_wait_time(2500);
    timer_cursor_visibility.set_one_shot(true);
    timer_cursor_visibility.set_callback([&]()
                                         {
        is_cursor_visible = false;
    });
}

Player::~Player(){}

void Player::on_update(int delta, Camera& camera)
{
    int direction = is_move_right_btn_pressed - is_move_left_btn_pressed;
    if(direction != 0 && !is_attacking_ex)
    {
        is_facing_right = direction > 0;
        current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
        float distance = run_velocity * delta * direction;
        on_run(distance);
    }
    else if(direction != 0 && is_attacking_ex)
    {
        is_facing_right = direction > 0;
        current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
        timer_run_effect_generation.pause();
    }
    else if(direction == 0 && is_attacking_ex)
    {
        current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
        timer_run_effect_generation.pause();
    }
    else
    {
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        timer_run_effect_generation.pause();
    }
    current_animation->on_update(delta);
    animation_jump_effect.on_update(delta);
    animation_land_effect.on_update(delta);
    timer_attack_cd.on_update(delta);
    timer_invulnerable.on_update(delta);
    timer_invulnerable_blink.on_update(delta);
    timer_run_effect_generation.on_update(delta);
    timer_cursor_visibility.on_update(delta);

    if (HP <= 0)
    {
        timer_die_effect_generation.on_update(delta);
        if(!is_die_animation_begin)
        {
            velocity.setX(last_hurt_direction < 0 ? 0.35f : -0.35f);
            velocity.setY(-1.0f);
            is_die_animation_begin = true;
        }

    }
    particle_list.erase(std::remove_if(
        particle_list.begin(), particle_list.end(),
        [](const Particle& particle)
        {
            return !particle.check_valid();
        }),
                        particle_list.end());
    for(Particle& particle : particle_list)
        particle.on_update(delta, camera);
    if (is_showing_sketch_frame)
    {
        img_sketch = QImage(current_animation->get_frame().width(), current_animation->get_frame().height(), QImage::Format_ARGB32_Premultiplied);
        img_sketch.fill(Qt::transparent);
        sketch_img(current_animation->get_frame(), img_sketch);
    }
    qDebug() << velocity.x();
}

void Player::on_draw(QPainter* widget_painter, const Camera& my_camera)
{

    for(const Particle& particle : particle_list)
    {
        particle.on_draw(widget_painter, my_camera);
    }
    const QVector2D pos_camera = my_camera.get_position();
    if(is_jump_effect_visible)
    {
        animation_jump_effect.on_draw((int)position_jump_effect.x() + pos_camera.x(), (int)position_jump_effect.y() + pos_camera.y(), widget_painter);
    }
    if(is_land_effect_visible)
    {
        animation_land_effect.on_draw((int)position_land_effect.x() + pos_camera.x(), (int)position_land_effect.y() + pos_camera.y(), widget_painter);
    }
    if( HP > 0 && is_invulnerable && is_showing_sketch_frame)
        widget_painter->drawImage(QPoint(position.x() + pos_camera.x(), position.y() + pos_camera.y()), img_sketch);
    else
        current_animation->on_draw(position.x() + pos_camera.x(), position.y() + pos_camera.y(), widget_painter);

    if(is_cursor_visible)
    {
        switch (id) {
        case PlayerID::P1:
            widget_painter->drawImage(QPoint(position.x() + (shape.x() - img_1P_cursor.width()) / 2 + pos_camera.x(), position.y() - img_1P_cursor.height() + pos_camera.y()), img_1P_cursor);
            break;
        case PlayerID::P2:
            widget_painter->drawImage(QPoint(position.x() + (shape.x() - img_2P_cursor.width()) / 2 + pos_camera.x(), position.y() - img_2P_cursor.height() + pos_camera.y()), img_2P_cursor);
            break;
        }
    }


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
    timer_run_effect_generation.resume();
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
    is_jump_effect_visible = true;
    animation_jump_effect.reset();

    float effect_frame_width = animation_jump_effect.get_frame().width();
    float effect_frame_height = animation_jump_effect.get_frame().height();
    position_jump_effect.setX( position.x() + (shape.x() - effect_frame_width) / 2);
    position_jump_effect.setY( position.y() + shape.y() - effect_frame_height);
}

void Player::on_land()
{
    is_land_effect_visible = true;
    animation_land_effect.reset();

    float effect_frame_width = animation_jump_effect.get_frame().width();
    float effect_frame_height = animation_jump_effect.get_frame().height();
    position_land_effect.setX( position.x() + (shape.x() - effect_frame_width) / 2);
    position_land_effect.setY( position.y() + shape.y() - effect_frame_height);
}

void Player::on_attack()
{

}

void Player::on_attack_ex()
{

}

void Player::make_invulnerable()
{
    is_invulnerable = true;
    timer_invulnerable.restart();
}

bool Player::if_invulnerable()
{
    return is_invulnerable;
}

int Player::get_hp() const
{
    return HP;
}

int Player::get_mp() const
{
    return MP;
}

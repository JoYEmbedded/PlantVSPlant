#include "peashootplayer.h"

PeashootPlayer::PeashootPlayer()
{
    animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
    animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
    animation_run_left.set_atlas(&atlas_peashooter_run_left);
    animation_run_right.set_atlas(&atlas_peashooter_run_right);
    animation_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
    animation_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);

    animation_idle_left.set_interval(75);
    animation_idle_right.set_interval(75);
    animation_run_left.set_interval(75);
    animation_run_right.set_interval(75);
    animation_attack_ex_left.set_interval(75);
    animation_attack_ex_right.set_interval(75);

    shape.setX(96);
    shape.setY(96);

    timer_attack_ex.set_wait_time(attack_ex_duration);
    timer_attack_ex.set_one_shot(true);
    timer_attack_ex.set_callback([&](){is_attacking_ex = false;});

    timer_spawn_pea_ex.set_wait_time(100);
    timer_spawn_pea_ex.set_one_shot(false);
    timer_spawn_pea_ex.set_callback([&](){spawn_pea_bullet(speed_pea_ex);});

    attack_cd = 200;
    timer_attack_cd.set_wait_time(attack_cd);
}

PeashootPlayer::~PeashootPlayer(){}

void PeashootPlayer::on_update(int delta)
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
    }
    else if(direction == 0 && is_attacking_ex)
    {
        current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
    }
    else
    {
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
    }
    current_animation->on_update(delta);
    timer_attack_cd.on_update(delta);
    timer_invulnerable.on_update(delta);
    timer_invulnerable_blink.on_update(delta);

    if (is_showing_sketch_frame)
    {
        img_sketch = QImage(current_animation->get_frame().width(), current_animation->get_frame().height(), QImage::Format_ARGB32_Premultiplied);
        img_sketch.fill(Qt::transparent);
        sketch_img(current_animation->get_frame(), img_sketch);
    }
    if (is_attacking_ex)
    {
        //shake
        timer_attack_ex.on_update(delta);
        timer_spawn_pea_ex.on_update(delta);
    }
}

void PeashootPlayer::on_draw(QPainter* widget_painter)
{
    Player::on_draw(widget_painter);
}

void PeashootPlayer::on_input(QKeyEvent* event, KeyType key_type)
{
    Player::on_input(event, key_type);
}

void PeashootPlayer::spawn_pea_bullet(float speed)
{
    Bullet* bullet = new PeaBullet();
    QVector2D bullet_position, bullet_velocity;
    const QVector2D& bullet_size = bullet->get_size();
    bullet_position.setX(is_facing_right
                             ? position.x() + shape.x() - bullet_size.x() / 2
                             : position.x() - bullet_size.x() / 2);
    bullet_position.setY(position.y());
    bullet_velocity.setX(is_facing_right ? speed : -speed);
    bullet_velocity.setY(0);

    bullet->set_position(bullet_position.x(), bullet_position.y());
    bullet->set_velocity(bullet_velocity.x(), bullet_velocity.y());
    bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
    bullet->set_callback([&](){MP += 25;});
    bullet_list.push_back(bullet);
}

void PeashootPlayer::on_attack()
{
    spawn_pea_bullet(speed_pea);
    switch (rand()%2) {
    case 0:
        music_pea_shoot_1->play();
        break;
    case 1:
        music_pea_shoot_2->play();
        break;
    }
}

void PeashootPlayer::on_attack_ex()
{
    is_attacking_ex = true;
    timer_attack_ex.restart();
    is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

    music_pea_shoot_ex->play();
}

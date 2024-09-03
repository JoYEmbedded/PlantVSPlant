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

    attack_cd = 100;
}

PeashootPlayer::~PeashootPlayer(){}

void PeashootPlayer::on_update(int delta)
{
    Player::on_update(delta);
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
        music_pea_shoot_1.setAudioOutput(music_audio_output);
        music_pea_shoot_1.play();
        break;
    case 1:
        music_pea_shoot_2.setAudioOutput(music_audio_output);
        music_pea_shoot_2.play();
        break;
    }
}

void PeashootPlayer::on_attack_ex()
{
    is_attacking_ex = true;
    timer_attack_ex.restart();

    is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
    music_pea_shoot_ex.setAudioOutput(music_audio_output);
    music_pea_shoot_ex.play();
}

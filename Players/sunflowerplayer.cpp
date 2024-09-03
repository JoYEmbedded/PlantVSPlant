#include "sunflowerplayer.h"

SunflowerPlayer::SunflowerPlayer()
{
    animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
    animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
    animation_run_left.set_atlas(&atlas_sunflower_run_left);
    animation_run_right.set_atlas(&atlas_sunflower_run_right);
    animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
    animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);

    animation_idle_left.set_interval(75);
    animation_idle_right.set_interval(75);
    animation_run_left.set_interval(75);
    animation_run_right.set_interval(75);
    animation_attack_ex_left.set_interval(100);
    animation_attack_ex_right.set_interval(100);

    animation_attack_ex_left.set_loop(false);
    animation_attack_ex_right.set_loop(false);
    animation_sun_text.set_loop(false);
    animation_attack_ex_left.set_callback([&]()
                                          {
                                is_attacking_ex = false;
                                is_sun_text_visible = false;

    });

    animation_attack_ex_right.set_callback([&](){
                                 is_attacking_ex = false;
                                 is_sun_text_visible = false;
    });
    shape.setX(96);
    shape.setY(96);

    attack_cd = 250;
}

SunflowerPlayer::~SunflowerPlayer(){}

void SunflowerPlayer::on_update(int delta)
{
    Player::on_update(delta);
    if(is_sun_text_visible)
        animation_sun_text.on_update(delta);
}

void SunflowerPlayer::on_draw(QPainter* widget_painter)
{
    Player::on_draw(widget_painter);
    if (is_sun_text_visible)
    {
        QVector2D text_position;
        QImage frame = animation_sun_text.get_frame();
        text_position.setX(position.x() - (shape.x() - frame.width()) / 2);
        text_position.setY(position.y() - frame.height());
        animation_sun_text.on_draw(text_position.x(), text_position.y(), widget_painter);
    }
}

void SunflowerPlayer::on_input(QKeyEvent* event, KeyType key_type)
{
    Player::on_input(event, key_type);
}

void SunflowerPlayer::on_attack()
{
    Bullet* bullet = new SunBullet();
    QVector2D bullet_position;
    const QVector2D& bullet_size = bullet->get_size();
    bullet_position.setX(position.x() + (shape.x() - bullet_size.x()) / 2);
    bullet_position.setY(position.y());

    bullet->set_position(bullet_position.x(), bullet_position.y());
    bullet->set_velocity(is_facing_right ? velocity_sun.x() : -velocity_sun.x(), velocity_sun.y());
    bullet->set_callback([&](){MP += 35;});
    bullet_list.push_back(bullet);
}

void SunflowerPlayer::on_attack_ex()
{
    is_attacking_ex = true;
    is_sun_text_visible = true;

    animation_sun_text.reset();
    is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

    Bullet* bullet = new SunBulletEx();
    Player* target_player = (id == PlayerID::P1 ? player_2 : player_1);
    QVector2D bullet_position, bullet_velocity;

    const QVector2D& bullet_size = bullet->get_size();
    const QVector2D& target_size = target_player->get_shape();
    const QPoint& target_position = target_player->get_position();

    bullet_position.setX(target_position.x() + (target_size.x() - bullet_size.x()) / 2);
    bullet_position.setY( - shape.y());
    bullet_velocity.setX(0);
    bullet_velocity.setY(speed_sun_ex);
    bullet->set_position(bullet_position.x(), bullet_position.y());
    bullet->set_velocity(bullet_velocity.x(), bullet_velocity.y());

    bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
    bullet->set_callback([&](){MP += 50;});
    bullet_list.push_back(bullet);

    music_sun_text.setAudioOutput(music_audio_output);
    music_sun_text.play();
}

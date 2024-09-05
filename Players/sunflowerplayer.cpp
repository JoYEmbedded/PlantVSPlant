#include "sunflowerplayer.h"

SunflowerPlayer::SunflowerPlayer()
{
    animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
    animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
    animation_run_left.set_atlas(&atlas_sunflower_run_left);
    animation_run_right.set_atlas(&atlas_sunflower_run_right);
    animation_sun_text.set_atlas(&atlas_sun_text);
    animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
    animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);

    animation_idle_left.set_interval(75);
    animation_idle_right.set_interval(75);
    animation_run_left.set_interval(75);
    animation_run_right.set_interval(75);
    animation_sun_text.set_interval(100);
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

    timer_attack_cd.set_wait_time(attack_cd);
}

SunflowerPlayer::~SunflowerPlayer(){}

void SunflowerPlayer::on_update(int delta)
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
        text_position.setX(position.x() + (shape.x() - frame.width()) / 2);
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
    bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
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

#include "sunflowerplayer.h"

SunflowerPlayer::SunflowerPlayer()
{
    animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
    animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
    animation_run_left.set_atlas(&atlas_sunflower_run_left);
    animation_run_right.set_atlas(&atlas_sunflower_run_right);

    animation_idle_left.set_interval(75);
    animation_idle_right.set_interval(75);
    animation_run_left.set_interval(75);
    animation_run_right.set_interval(75);

    shape.setX(96);
    shape.setY(96);
}

SunflowerPlayer::~SunflowerPlayer(){}

void SunflowerPlayer::on_update(int delta)
{
    Player::on_update(delta);
}

void SunflowerPlayer::on_draw(QPainter* widget_painter)
{
    Player::on_draw(widget_painter);
}

void SunflowerPlayer::on_input(QKeyEvent* event, KeyType key_type)
{
    Player::on_input(event, key_type);
}

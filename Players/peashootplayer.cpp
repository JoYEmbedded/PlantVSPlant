#include "peashootplayer.h"

PeashootPlayer::PeashootPlayer()
{
    animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
    animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
    animation_run_left.set_atlas(&atlas_peashooter_run_left);
    animation_run_right.set_atlas(&atlas_peashooter_run_right);

    animation_idle_left.set_interval(75);
    animation_idle_right.set_interval(75);
    animation_run_left.set_interval(75);
    animation_run_right.set_interval(75);

}

PeashootPlayer::~PeashootPlayer(){}

void PeashootPlayer::on_update(int delta)
{
    Player::on_update(delta);
}

void PeashootPlayer::on_draw(QPainter* widget_painter)
{
    Player::on_draw(widget_painter);
}

void PeashootPlayer::on_input(QKeyEvent* event, KeyType key_type)
{
    Player::on_input(event, key_type);
}

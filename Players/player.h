#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QPainter>
#include "graphics/animation.h"
#include "player_id.h"
class Player
{
public:
    Player();
    ~Player();

    int HP = 100;
    int MP = 100;

    virtual void on_update(int delta);
    virtual void on_draw(QPainter* widget_painter);
    virtual void on_input();

protected:
    QPoint position;

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;

};

#endif // PLAYER_H

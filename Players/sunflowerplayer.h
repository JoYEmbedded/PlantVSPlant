#ifndef SUNFLOWERPLAYER_H
#define SUNFLOWERPLAYER_H
#include "player.h"
#include <QPainter>
class SunflowerPlayer : public Player
{
public:
    SunflowerPlayer();
    ~SunflowerPlayer();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input();
};

#endif // SUNFLOWERPLAYER_H

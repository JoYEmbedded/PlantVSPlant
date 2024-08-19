#ifndef SUNFLOWERPLAYER_H
#define SUNFLOWERPLAYER_H
#include "player.h"
#include <QPainter>

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;

class SunflowerPlayer : public Player
{
public:
    SunflowerPlayer();
    ~SunflowerPlayer();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input(QKeyEvent* event, KeyType key_type);
};

#endif // SUNFLOWERPLAYER_H
